import { Component, OnInit } from '@angular/core';
import * as firebase from 'firebase';
import { auth } from 'firebase';
import { AngularFireAuth } from '@angular/fire/auth';
import { generateUserData, UserData } from '../types';
import { DbServiceService } from '../db-service.service';

@Component({
  selector: 'app-welcome-user',
  templateUrl: './welcome-user.page.html',
  styleUrls: ['./welcome-user.page.scss'],
})
export class WelcomeUserPage implements OnInit {
  name: string = null;
  user: UserData = null;

  constructor(private afAuth: AngularFireAuth, private dbService: DbServiceService) {
    this.afAuth.authState.subscribe(user => {
      console.log(user);
        this.user = generateUserData(user);
        this.dbService.startDataInterface();

      }
    );

  }

  ngOnInit() {
  }

}
