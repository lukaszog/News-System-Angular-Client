'use strict';

describe('Controller: NowywidokCtrl', function () {

  // load the controller's module
  beforeEach(module('angularAppApp'));

  var NowywidokCtrl,
    scope;

  // Initialize the controller and a mock scope
  beforeEach(inject(function ($controller, $rootScope) {
    scope = $rootScope.$new();
    NowywidokCtrl = $controller('NowywidokCtrl', {
      $scope: scope
    });
  }));

  it('should attach a list of awesomeThings to the scope', function () {
    expect(scope.awesomeThings.length).toBe(3);
  });
});
