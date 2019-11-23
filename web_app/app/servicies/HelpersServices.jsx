export const HelpersServices = {
    removeEmptyKeys
};

function isEmpty(val) {
    return undefined === val || null === val || 0 === val.length;
}

function removeEmptyKeys(object) {
    for(let key in object) {
        if(isEmpty(object[key])) {
            delete object[key];
        }
    }
    return object;
}