import {HelpersServices} from './HelpersServices.jsx';
import {UserService} from './UserService.jsx';

import config from '../config/config.json';

export const RequestService = {
    fetchUrl,
};

function fetchUrl(url, data, callback, method = 'GET') {
    const requestOptions = {
        credentials: 'include',
        headers: {'Content-Type': 'application/json'},
        method: method,
        mode: 'cors'
    };
    if(null !== data) {
        requestOptions.body = JSON.stringify(HelpersServices.removeEmptyKeys(data));
    }

    fetch('http://' + config.location + ':' + config.port + url, requestOptions)
        .then(response => {
            if (!response.ok) {
                if (401 === response.status) {
                    UserService.logout();
                }
            }
            return response.json();
        })
        .then(data => {
            if('error' === data.result) {
                console.error('Error:', data);
            }
            if(null !== callback) {
                callback(data);
            }
        }).catch(error => {
            console.error('Connection error:', error);
            if(null !== callback) {
                callback({errors: ['message.connectionError'], result: 'error'});
            }
        });
}