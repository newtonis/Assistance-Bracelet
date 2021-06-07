import { Observable } from 'rxjs';
import { User } from 'firebase';

export interface UserData{
    id: string;
    name: string;
    email: string;
    image_url: string;
}

export function generateUserData(user: firebase.User) : UserData{
    return {
        id: user.uid,
        name: user.displayName,
        email: user.email,
        image_url: user.photoURL
    }
}

export interface Medicine{
    name: string;
    
    startTime: number;
    endTime: number;
    
};

export interface Bracelet{
    name: string;
    medicine: Medicine[];
}

