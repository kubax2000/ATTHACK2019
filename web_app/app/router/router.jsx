import {createBrowserHistory} from 'history';
import {Redirect, Route, Router, Switch} from 'react-router-dom';
import layouts from '../layouts/index.jsx';
import {PositionService} from '../servicies/PositionService.jsx';
import React, {Component, Suspense} from 'react';
import {UserService} from '../servicies/UserService.jsx';
import views from '../views/index.jsx';

export default function App() {
    PositionService.run();
    const history = createBrowserHistory();
    UserService.setHistory(history);
    return (
        <Router history={history}>
            <Suspense fallback={(<div>Loading</div>)}>
                <Switch>
                    <Route path="/sign-in" component={views.SignIn} />
                    <PrivateRoute path="/">
                        <layouts.Default>
                            <Switch>
                                <Route exact path="/" component={views.Homepage} />
                            </Switch>
                        </layouts.Default>
                    </PrivateRoute>
                </Switch>
            </Suspense>
        </Router>
    );
}

const PrivateRoute = ({component: Component, children: Children, ...rest}) => {
    if(!UserService.isLoggedIn()) {
        return <Redirect to="/sign-in" />
    }
    return <Route {...rest} render={props => (undefined !== Component ? <Component {...props} /> : Children)}/>;
};
