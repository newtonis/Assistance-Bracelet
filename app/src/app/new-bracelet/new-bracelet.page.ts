import { Component, OnInit } from '@angular/core';
import { AngularFireAuth } from '@angular/fire/auth';
import { User } from 'firebase';
import { Timestamp } from 'rxjs';
import { DbServiceService } from '../db-service.service';
import { ToastController } from '@ionic/angular';
import { Router } from '@angular/router';

@Component({
  selector: 'app-new-bracelet',
  templateUrl: './new-bracelet.page.html',
  styleUrls: ['./new-bracelet.page.scss'],
})
export class NewBraceletPage implements OnInit {

  firstname: string;
  lastname: string;
  surname: string;
  birthday: number;
  user: User;

  constructor(private router: Router, private toastController: ToastController, private afAuth: AngularFireAuth, private dbService: DbServiceService) { }

  ngOnInit() {
    this.afAuth.authState.subscribe(user => {
        console.log(user);
        this.user = user;
      }
    );
  }

  sendBraceletData(){
    const thisReference = this;

    this.dbService.addBracelet(
      this.surname,
      this.firstname,
      this.lastname,
      this.birthday,
      this.user.uid
    ).then(function(){
      thisReference.presentToast(thisReference, "Pulsera agregada"); // Luego de agregar los datos mostramos el toast
      thisReference.router.navigateByUrl("/handle-bracelets");
    }).catch(function(){
      thisReference.presentToast(thisReference, "Error detectado");
    });
  }
  async presentToast(thisReference: any, text: string) {
    const toast = await thisReference.toastController.create({
      message: text,
      duration: 800
    });
    toast.present();
  }

}
