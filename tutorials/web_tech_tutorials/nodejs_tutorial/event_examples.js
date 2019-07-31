
var events = require('events')
var util = require('util')


var Person = function(name) {
    this.name = name;
}


util.inherits(Person, events.EventEmitter);     // how to inherit, Person inherits EventEmitter

var james = new Person('james')
var mary = new Person('mary')
var ryu = new Person('ryu')

var people = [james, mary, ryu]

people.forEach( function(person) {
    person.on('speak', function(msg) {
        console.log(person.name + ' said: ' + msg)
    })
} )

mary.emit('speak', 'Hi, I am Mary!');
ryu.emit('speak', 'I want a curry');





var emitExample = function() {
    var myEmitter = new events.EventEmitter()
    myEmitter.on('someEvent', function(msg) {
            console.log(msg);
        } 
    )


    myEmitter.emit('someEvent', 'the event was emitted')
}
