import {Button, Checkbox, Form, Icon, Input, Label, List, Message, Select, Transition} from 'semantic-ui-react';
import React, {useState} from 'react';
import {RequestService} from '../../servicies/RequestService.jsx';

export default function CrossroadForm() {
    const [state, setState] = useState({crossroad_key: ''});

    const handleSelectChange = (event, data) => {
        let newState = Object.assign({}, state);
        newState[data.name] = data.value;
        setState(newState);
    };
    const handleSubmit = () => {
        RequestService.fetchUrl('');
    };

    return (
        <Form>
            <Form.Field>
                Are you on crossroad in 60 seconds?
            </Form.Field>
            <Form.Field>
                <label>Crossroad</label>
                <Select name="crossroad_key" onChange={handleSelectChange} options={[{key: 'sv', value: 'sv', text: 'Severo východ'},{key: 'sz', value: 'sz', text: 'Severo západ'},{key: 'jv', value: 'jv', text: 'Jiho východ'},{ key: 'jz', value: 'jz', text: 'Jiho západ'}]} placeholder={'Select crossroad'} />
            </Form.Field>
            <Form.Field color="blue" control={Button} onClick={handleSubmit}>Send</Form.Field>
        </Form>
    );
}