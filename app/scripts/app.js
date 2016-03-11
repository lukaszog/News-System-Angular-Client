'use strict';

/**
 * @ngdoc overview
 * @name angularAppApp
 * @description
 * # angularAppApp
 *
 * Main module of the application.
 */
angular
  .module('angularAppApp', [
    'ngAnimate',
    'ngCookies',
    'ngResource',
    'ngRoute',
    'ngSanitize',
    'ngTouch',
    'RESTService'
  ])
  .config(function ($routeProvider) {
    $routeProvider
      .when('/', {
        templateUrl: 'views/main.html',
        controller: 'NewsController',
        controllerAs: 'dashboard'
      })
      .when('/about', {
        templateUrl: 'views/about.html',
        controller: 'NewsController',
        controllerAs: 'dashboard'
      })
      .when('/nowywidok', {
        templateUrl: 'views/nowywidok.html',
        controller: 'NowywidokCtrl'
      })
      .otherwise({
        redirectTo: '/'
      });
  });

