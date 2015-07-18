
var SAMPLE_DATA = {
    votes : {
        PRI : 1,
        PAN : 1,
        PRD : 1,
        P_T : 1,
        VDE : 1,
        MVC : 1,
        NVA : 1,
        MOR : 1,
        HUM : 1,
        ENC : 1
    },
    total : 7
}


var parties = [
    {
        key : 'PRI',
        name : 'PRI',
        color : '',
        image : 'PRI.png'
    },
    {
        key : 'PAN',
        name : 'PAN',
        color : '',
        image : 'PAN.png'
    },
    {
        key : 'PRD',
        name : 'PRD',
        color : '',
        image : 'PRD.png'
    },
    {
        key : 'P_T',
        name : 'PT',
        color : '',
        image : 'P_T.png'
    },
    {
        key : 'VDE',
        name : 'Partido Verde',
        color : '',
        image : 'VDE.png'
    },
    {
        key : 'MVC',
        name : 'Movimiento Ciudadano',
        color : '',
        image : 'MVC.png'
    },
    {
        key : 'NVA',
        name : 'Nueva Alianza',
        color : '',
        image : 'NVA.png'
    },
    {
        key : 'MOR',
        name : 'MORENA',
        color : '',
        image : 'MOR.jpg'
    },
    {
        key : 'HUM',
        name : 'Partido Humanista',
        color : '',
        image : 'HUM.png'
    },
    {
        key : 'ENC',
        name : 'Encuentro Ciudadano',
        color : '',
        image : 'ENC.jpg'
    },
];

var Party = function (data) {
    this.key = data.key;
    this.name = data.name;
    this.color = data.color;
    this.image = data.image;
    this.votes = 0;
    this.position = 0;
}

Party.prototype.getHTML = function () {

    return '\
        <li class="party"> \
            <div \
                style="background-image: url(\'https://robohash.org/' + this.key + '.png?set=set2\')" \
                class="profile-icon" data-position="' + this.position + '"> \
                <div \
                    style="background-image: url(\'./logos/' + this.image + '\')" \
                    class="party-icon-mini"></div> \
            </div> \
            <div class="profile-name">70,000,000</div> \
            <div class="profile-votes">70,000,000</div> \
        </li> \
    '
}


function updateParties(votes) {

    parties.forEach(function(party){
        party.votes = votes[party.key];
    });

    parties.sort('votes');

    var elements = parties.map(function (party, index) {
        party.position = index + 1;
        return party.getHTML();
    });

    $POSITIONS_LIST.innerHTML = elements.join('');
}



var $POSITIONS_LIST = null;

document.addEventListener("DOMContentLoaded", function(event) {

    $POSITIONS_LIST = document.querySelector('#positions');

    parties = parties.map(function (item) {
        return new Party(item);
    });

    updateParties(SAMPLE_DATA.votes);

});
