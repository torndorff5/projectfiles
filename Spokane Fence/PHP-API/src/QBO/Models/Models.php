<?php

namespace QBO\Models;

class Customer {
    var $displayname, $title, $givenname,$middlename, $suffix, $familyname,$primaryemailaddr,$mobile,$alternatephone,$shipaddr;
}
class Addr{
    var $address, $city, $postalcode, $lat, $long, $subdivisioncode;
}