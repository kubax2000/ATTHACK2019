import config from '../config/config.json';
import {RequestService} from './RequestService.jsx';

export const UserService = {
    getUserIdentity,
    isLoggedIn,
    login,
    logout,
    setHistory
};

const userServiceData = {
    history: undefined,
    user: {
        identity: {
            Name: undefined
        },
        isLoggedIn: false
    }
};

(function() {
    let storage = localStorage.getItem('user-service-data');
    if(null !== storage) {
        let storageData = JSON.parse(storage);
        if(config.version === storageData.version) {
            userServiceData.user = storageData;
        }
    }
}());

function getUserIdentity() {
    return userServiceData.user.identity;
}

function isLoggedIn() {
    return userServiceData.user.isLoggedIn;
}

function login(name) {
    userServiceData.user.isLoggedIn = true;
    userServiceData.user.identity.Name = name;
    userServiceData.history.push('/');
}

function logout() {
    localStorage.setItem('user-service-data', '{}');
    userServiceData.user.identity = {};
    userServiceData.user.isLoggedIn = false;
    userServiceData.history.push('/sign-in');
}

function setHistory(history) {
    userServiceData.history = history;
}