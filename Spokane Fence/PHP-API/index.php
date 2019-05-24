<?php
use \Psr\Http\Message\ServerRequestInterface as Request;
use \Psr\Http\Message\ResponseInterface as Response;
use QuickBooksOnline\API\DataService\DataService;
use QuickBooksOnline\API\Core\OAuth\OAuth2\OAuth2AccessToken;
use QuickBooksOnline\API\Facades\Customer;
//use \QBO\Middleware\Logging as Logger;

require 'vendor/autoload.php';

function dataInit(){
    $config = include('config.php');
    $dataService = DataService::Configure(array(
        'auth_mode' => 'oauth2',
        'ClientID' => $config['client_id'],
        'ClientSecret' =>  $config['client_secret'],
        'RedirectURI' => $config['oauth_redirect_uri'],
        'scope' => $config['oauth_scope'],
        'baseUrl' => "development"
    ));
    return $dataService;
}
function setAccessTokenJson(array $accessTokenJson){
    $config = include('config.php');
    $jsonFile = $config['file'];
    //write $accesstokenjson to file
    file_put_contents($jsonFile,serialize($accessTokenJson));
}
function getAccessTokenJson(){
    $config = include('config.php');
    $jsonFile = $config['file'];
    //get $accesstokejson from file
    if(filesize($jsonFile) == 0)
        return null;
    else{
        $accessTokenJson = unserialize(file_get_contents($jsonFile));
        return $accessTokenJson;
    }
}
function initAccessToken($token){
    $config = include('config.php');
    $accessTokenObject = new OAuth2AccessToken($config['client_id'],$config['client_secret']);
    $accessTokenObject->setAccessToken($token);
    $accessTokenObject->setRealmID($config['realmId']);
    return $accessTokenObject;
}

function initAccessTokenJson(OAuth2AccessToken $accessToken){
    $accessTokenJson = array('token_type' => 'bearer',
        'access_token' => $accessToken->getAccessToken(),
        'refresh_token' => $accessToken->getRefreshToken(),
        'x_refresh_token_expires_in' => $accessToken->getRefreshTokenExpiresAt(),
        'expires_in' => $accessToken->getAccessTokenExpiresAt()
    );
    return $accessTokenJson;
}

//call authenticate code here
//initiate data service
$dataService = dataInit();
$OAuth2LoginHelper = $dataService->getOAuth2LoginHelper();
$authUrl = $OAuth2LoginHelper->getAuthorizationCodeURL();


$app = new \Slim\App;

/**
 * delivers the return code to the application that called
 */
$app->get('/redirect', function (Request $request, Response $response, array $args){
    $params = $request->getQueryParams();
    $code = $params['code'];
    $realmId = $params['realmId'];
    $dataService = dataInit();
    $OAuth2LoginHelper = $dataService->getOAuth2LoginHelper();
    $accessToken = $OAuth2LoginHelper->exchangeAuthorizationCodeForToken($code,$realmId);
    $dataService->updateOAuth2Token($accessToken);
    $accessTokenJson = initAccessTokenJson($accessToken);
    //send Json to app
    setAccessTokenJson($accessTokenJson);
    return $response->getBody()->write("Success!");
});

/**
 * redirects request to the auth URL that is initialized above.
 */
$app->redirect('/authenticate', $authUrl,302);

/**
 * gives access token to authorized user if provided the correct username and password
 */
$app->post('/authenticate/{username}/{password}', function (Request $request, Response $response, array $args) {
    $config = include('config.php');
    $accessTokenJson = getAccessTokenJson();
    if(($args['username']!=$config['client_id'])||($args['password']!=$config['client_secret']))
        return $response->withStatus(401);
    else
        return $response->withJson($accessTokenJson,201);
});
$app->get('/customers', function (Request $request, Response $response, array $args) {
    //get all customers in QBO
    $dataService = dataInit();
    $headers = $request->getHeader('accessToken');
    $token = $headers[0];
    $accessTokenObject = initAccessToken($token);
    $dataService->updateOAuth2Token($accessTokenObject);
    $customers = $dataService->Query("SELECT * FROM Customer");
    return $response->withJson($customers,201);
});
$app->post('/customers', function (Request $request, Response $response, array $args) {
    //get all customers in QBO
    $cus = $request->getBody();
    $resourceObj = Customer::create(json_decode($cus,true));
    $dataService = dataInit();
    $headers = $request->getHeader('access_token');
    $token = $headers[0];
    $accessTokenObject = initAccessToken($token);
    $dataService->updateOAuth2Token($accessTokenObject);
    $resultingObj = $dataService->Add($resourceObj);
    $error = $dataService->getLastError();
    if($error){
        print($error);
    }
    else{
        return $response->withJson($resultingObj,200);
    }
});
$app->post('/customers/update', function (Request $request, Response $response, array $args) {
    //get all customers in QBO
    $cus = $request->getBody();
    $resourceObj = Customer::create(json_decode($cus,true));
    $dataService = dataInit();
    $headers = $request->getHeader('access_token');
    $token = $headers[0];
    $accessTokenObject = initAccessToken($token);
    $dataService->updateOAuth2Token($accessTokenObject);
    $resultingObj = $dataService->Update($resourceObj);
    $error = $dataService->getLastError();
    if($error){
        print("The Status code is: " . $error->getHttpStatusCode() . "\n");
        print("The Helper message is: " . $error->getOAuthHelperError() . "\n");
        print("The Response message is: " . $error->getResponseBody() . "\n");
    }
    else{
        return $response->withJson($resultingObj,200);
    }
});

$app->get('/customers/{id:[0-9]+}', function (Request $request, Response $response, array $args) {
    if(isset($_SESSION['sessionAccessToken'])){
        $dataService = $_SESSION['dataService'];
        $customer = $dataService->FindByID('customer', $args['id']);
        return $response->withJson($customer,200);
    }
    else
        return $response->getBody()->write("No access token.");
});
$app->get('/customers/{lastname}', function (Request $request, Response $response, array $args) {
    if(isset($_SESSION['sessionAccessToken'])){
        $dataService = $_SESSION['dataService'];
        $customer = $dataService->Query("SELECT * FROM Customer WHERE FamilyName='{$args['lastname']}'");
        return $response->withJson($customer,200);
    }
    else
        return $response->getBody()->write("No access token.");
});
$app->run();
