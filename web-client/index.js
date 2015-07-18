var APP = {
    positionList : null,
    chart : null,
    socketURL : 'http://192.168.0.7:8080',
    httpURL : 'http://192.168.0.7:8081',
    socket : null,
    parties : PARTIES_DATA
}

APP.init = function () {

    APP.socket = io(APP.socketURL);
    APP.positionList = document.querySelector('#positions');
    APP.chartElement = document.querySelector('#chart-container figure');

    APP.searchForm = document.querySelector('#search form');
    APP.txtCURP = document.querySelector('#txt-curp');
    APP.txtPhone = document.querySelector('#txt-phone');

    APP.serchResult = document.querySelector('#search-result');

    APP.chartElement = document.querySelector('#chart-container figure');

    APP.searchForm.addEventListener('submit', APP.onSearch);

    APP.parties = APP.parties.map(function (item) {
        return new Party(item);
    });

    APP.chart = new PieChart();

    APP.socket.on('update', function (data) {
        APP.updateParties(data.votes);
        APP.chart.update();
    });
}

APP.updateParties = function(votes) {

    APP.parties.forEach(function(party){
        party.votes = votes[party.key];
    });

    APP.parties.sort(function (a, b) {

        var value = (a.votes - b.votes) * -1;

        if(value === 0){
            return a.name > b.name;
        }

        return value;
    });

    var elements = APP.parties.map(function (party, index) {
        party.position = index + 1;
        return party.getHTML();
    });

    APP.positionList.innerHTML = elements.join('');
}

APP.onSearch = function (e) {
    e.preventDefault();

    var url = APP.httpURL + '/votes';
    url += '?curp=' + APP.txtCURP.value;
    url += '&phone=' + APP.txtPhone.value;

    fetch(url)
    .then(function (res) {
        return res.json();
    })
    .then(function (vote) {

        return APP.showSearchResult(vote);

    })
    .catch(function (err) {
        console.log(err)
        APP.showSearchResult();
    });

}

APP.showSearchResult = function (vote) {

    var html = ' \
        <div id="no-result"> \
            No se encontró ningún resultado \
        </div> \
    ';

    if(vote){

        var results = APP.parties.filter(function(party) {
            return party.key === vote.party;
        });

        if(results.length === 1){

            var party = results[0];

            var partyStyles = '';

            if(party.key !== 'FRD'){
                partyStyles = 'style="background-image: url(\'./logos/' + party.image + '\')"';
            }

            html = ' \
                <div \
                    style="background-image: url(\'https://robohash.org/' + party.key + '.png?set=set2\')" \
                    class="profile-icon"> \
                    <div class="party-icon-mini" ' + partyStyles + '></div> \
                </div> \
                <div class="profile-name"> \
                    <p> \
                        <strong>Partido:</strong> \
                        <span id="party-name">' + party.name + '</span> \
                    </p> \
                    <p> \
                        <strong>CURP:</strong> \
                        <span id="curp">' + vote.curp + '</span> \
                    </p> \
                    <p> \
                        <strong>Teléfono:</strong> \
                        <span id="phone">' + vote.phone + '</span> \
                    </p> \
                </div> \
            ';

        }


    }

    APP.serchResult.innerHTML = html;

    return true;
}

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
        ENC : 1,
        FRD : 1
    }
}




var Party = function (data) {
    this.key = data.key;
    this.name = data.name;
    this.color = data.color;
    this.image = data.image;
    this.votes = 0;
    this.position = 0;
}

Party.prototype.getHTML = function () {

    var partyStyles = '';

    if(this.key !== 'FRD'){
        partyStyles = 'style="background-image: url(\'./logos/' + this.image + '\')"';
    }

    return '\
        <li class="party"> \
            <div \
                style="background-image: url(\'https://robohash.org/' + this.key + '.png?set=set2\')" \
                class="profile-icon" data-position="' + this.position + '"> \
                <div class="party-icon-mini" ' + partyStyles + '></div> \
            </div> \
            <div class="profile-name">70,000,000</div> \
            <div class="profile-votes">' + this.votes + '</div> \
        </li> \
    '
}

var PieChart = function () {

    this.chart = new Chartist.Pie(APP.chartElement, {
        series : []
    });

    this.chart.on('draw', this.onDraw);

}

PieChart.prototype.sum = function(a, b) {
    return a + b.value
};


PieChart.prototype.onDraw = function(context) {

    if(context.type === 'slice') {

        context.element.attr({
            style: 'fill:' + context.meta
        });
    }

}

PieChart.prototype.update = function() {

    var series = APP.parties.map(function (party) {
        return {
            value : party.votes,
            meta : party.color
        };
    });

    var that = this;

    this.chart.update({
        series : series
    },{
        labelInterpolationFnc : function(value) {
            return Math.round(value / series.reduce(that.sum, 0) * 100) + '%';
        }
    });

};


document.addEventListener('DOMContentLoaded', APP.init);
