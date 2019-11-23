import {Button, Checkbox, Form, Icon, Input, Label, List, Message, Transition} from 'semantic-ui-react';
import React, {useState} from 'react';
import {UserService} from '../../servicies/UserService.jsx';

export default function SignInForm() {
    const [state, setState] = useState({nickname: ''});

    const handleInputChange = (event, data) => {
        let newState = Object.assign({}, state);
        newState[data.name] = data.value;
        setState(newState);
    };
    const handleSubmit = () => {
        UserService.login(state.nickname);
    };

    return (
        <Form>
            <Form.Field>
                <label>Nickname</label>
                <Input icon="user" iconPosition="left" name="nickname" onChange={handleInputChange} placeholder={'Nickname'} value={state.nickname} />
            </Form.Field>
            <Form.Field color="blue" control={Button} onClick={handleSubmit}>Sign in</Form.Field>
        </Form>
    );
}