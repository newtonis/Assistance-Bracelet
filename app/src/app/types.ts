import { Observable } from 'rxjs';
import { User } from 'firebase';
import { NumberValueAccessor } from '@angular/forms';


export interface UserData{
    id: string;
    name: string;
    email: string;
    image_url: string;
};

export function generateUserData(user: firebase.User) : UserData{
    return {
        id: user.uid,
        name: user.displayName,
        email: user.email,
        image_url: user.photoURL
    }
};

export function generateBracelet(
    firstname: string,
    lastname: string,
    surname: string,
    birthday: number
) : Bracelet{
    return {
        firstname: firstname,
        lastname: lastname,
        surname: surname,
        birthday: birthday,
        medicine: [],
        valid: true,
        bateryLvl: 0
    }
};

export interface dayTimes{
    dia: string;
    horario: number;
};

export interface Medicine{
    name: string;
    alarm: string;
    timetable: dayTimes[];
};

export interface Bracelet{
    firstname: string;
    lastname: string;
    surname: string;
    birthday: number;

    medicine: Medicine[];
    valid: boolean;
    bateryLvl: number;
};

