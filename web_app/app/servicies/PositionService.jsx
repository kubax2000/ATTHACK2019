
export const PositionService = {
    run
};

const run = () => {
    setInterval(run_callback, 100);
};

const run_callback = () => {
    navigator.geolocation.getCurrentPosition(console.log)
};