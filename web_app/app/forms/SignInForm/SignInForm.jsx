import {Button, Checkbox, Form, Icon, Input, Label, List, Message, Transition} from 'semantic-ui-react';
import config from '../../config/config.json';
import React, {useState} from 'react';
import {UserService} from '../../servicies/UserService.jsx';

export default function SignInForm() {
    const [state, setState] = useState({email: '', errors: [], loading: false, password: '', remember: false});

    const handleInputChange = (event, data) => {
        let newState = Object.assign({}, state);
        newState[data.name] = data.value;
        setState(newState);
    };
    const handleSubmit = () => {
        let newState = Object.assign({}, state);
        newState.errors = [];
        newState.loading = true;
        setState(newState);
        UserService.login(state.email, state.password, state.remember, (response) => {
            if ('success' === response.result) {
                history.push('/');
            } else {
                let newState = Object.assign({}, state);
                newState.errors = response.errors;
                newState.loading = false;
                setState(newState);
            }
        });
    };

    return (
        <Form>
            <Form.Field>
                <label>Nickname</label>
                <Input icon="user" iconPosition="left" name="nickname" onChange={handleInputChange} placeholder={'Nickname'} value={state.email} />
            </Form.Field>
            <Form.Field color="blue" control={Button} onClick={handleSubmit}>Sign in</Form.Field>
        </Form>
    );
}