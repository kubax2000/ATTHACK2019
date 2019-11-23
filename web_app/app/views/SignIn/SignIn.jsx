import SignInForm from '../../forms/SignInForm/SignInForm.jsx';
import React from 'react';
import styles from './SignIn.module.sass';

export default function Homepage() {
    return (
        <div className={styles.formBorder}>
            <div className={styles.form}>
                <SignInForm />
            </div>
        </div>
    );
}