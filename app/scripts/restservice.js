/**
 * Created by Lukasz on 2016-03-11.
 */
angular.module('RESTService', [])
  .controller('NewsController', function(NewsModel){
    var dashboard = this;
    function getItems(){
      NewsModel.all().then(function (result){
        //main.news = result.data;
        dashboard.items = result.data;
        console.log(dashboard.items);
      })
    }

    function createItem(item){
      NewsModel.create(item).then(function (result){
        initCreateForm();
        console.log(result);
      })
    }

    function initCreateForm(){
      dashboard.newItem = { title: '', author: ''};
    }

    dashboard.items = [];
    dashboard.createItem = createItem;

    initCreateForm();
    getItems();
  })
.constant('ENDPOINT_URI', 'http://localhost:8080/api/news/')
.service('NewsModel', function($http, ENDPOINT_URI){

  var service = this;
  path = 'saveNews/';

  function getUrl(){
    return ENDPOINT_URI + path;
  }

  service.all = function(){
    return $http.get(getUrl());
  }

  service.create = function(item){
    return $http.post(getUrl(),item);
  }

});
