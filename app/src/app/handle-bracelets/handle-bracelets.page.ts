import { Component, OnInit } from '@angular/core';
import { DbServiceService } from '../db-service.service';
import { Observable, BehaviorSubject } from 'rxjs';
import { Bracelet } from '../types';
import { AngularFireAuth } from '@angular/fire/auth';
import { generateUserData, UserData } from '../types';
import { Router } from '@angular/router';

@Component({
  selector: 'app-handle-bracelets',
  templateUrl: './handle-bracelets.page.html',
  styleUrls: ['./handle-bracelets.page.scss'],
})
export class HandleBraceletsPage implements OnInit {

  bracelets : Observable<Bracelet[]>;
  user: UserData = null;

  constructor(private router: Router, private afAuth: AngularFireAuth, private DbService: DbServiceService) { 
    this.afAuth.authState.subscribe(user => {
      console.log(user);
        this.user = generateUserData(user);
        this.DbService.askForBraceletData(this.user.id);
      }
    );
  }

  ngOnInit() {
    this.bracelets = this.DbService.getBraceletObs();
  }
  
  goToAddBracelet(){
    this.router.navigateByUrl("/new-bracelet");
  }

}
