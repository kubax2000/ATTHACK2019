

export const PositionService = {
    getInfo,
    run
};

const positionServiceData = {
    origin: {
        latitude: undefined,
        longitude: undefined,
        speed: undefined,
        timestamp: undefined
    }
};

function getInfo() {
    return positionServiceData.origin;
}

function run() {
    navigator.geolocation.watchPosition(position_success, position_error, {
        enableHighAccuracy: true,
        timeout: 5000,
        maximumAge: 0
    });
}

function position_error(err) {
    console.warn('ERROR(' + err.code + '): ' + err.message);
}

function position_success(position) {
    console.log(position);
    if(position.coords.latitude !== positionServiceData.origin.latitude || position.coords.longitude !== positionServiceData.origin.longitude) {
        if(position.coords.accuracy > 1000) {
            console.log('accuracy error');
            return;
        }
        if(undefined !== positionServiceData.origin.timestamp) {
            let lat1 = positionServiceData.origin.latitude / (180 / Math.PI);
            let lat2 = position.coords.latitude / (180 / Math.PI);
            let lon1 = positionServiceData.origin.longitude / (180 / Math.PI);
            let lon2 = position.coords.longitude / (180 / Math.PI);

            let dlon = lon2 - lon1;
            let dlat = lat2 - lat1;
            let a = Math.pow(Math.sin(dlat / 2), 2) + Math.cos(lat1) * Math.cos(lat2) * Math.pow(Math.sin(dlon / 2), 2);

            let c = 2 * Math.asin(Math.sqrt(a));

            positionServiceData.origin.speed = (c * 6371 * 1.609344 * 1000000) / (position.timestamp - positionServiceData.origin.timestamp);
        }
        positionServiceData.origin.latitude = position.coords.latitude;
        positionServiceData.origin.longitude = position.coords.longitude;
        positionServiceData.origin.timestamp = position.timestamp;
    }
}