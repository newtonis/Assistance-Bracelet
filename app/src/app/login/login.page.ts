import { Component, OnInit, ɵConsole } from '@angular/core';
import { FirebaseAuthentication } from '@ionic-native/firebase-authentication/ngx';
import firebase from 'firebase';
import { AngularFireAuth } from '@angular/fire/auth';
import {NavController, Platform} from '@ionic/angular';
import { auth } from 'firebase/app';
import EventEmitter from 'events';
import { GooglePlus } from '@ionic-native/google-plus/ngx';
import { promise } from 'protractor';
import { Router } from '@angular/router';
import { LoadingController } from '@ionic/angular';


@Component({
  selector: 'app-login',
  templateUrl: './login.page.html',
  styleUrls: ['./login.page.scss'],
})
export class LoginPage implements OnInit {
  loaded: boolean = false;
  loadingUI: HTMLIonLoadingElement = null;

  constructor(
    private googlePlus: GooglePlus,
    private platform: Platform,
    private afAuth: AngularFireAuth,
    private router: Router,
    private loadingController: LoadingController
  ) { }

  ngOnInit() {
  }

  async setLoading() {
    
    this.loadingUI = await this.loadingController.create({
      cssClass: 'my-custom-class',
      message: 'Please wait...',
    });
    if (!this.loaded){
      return await this.loadingUI.present();
    }
  }
  
  async dimissLoading(){
    return await this.loadingUI.dismiss();
  }
  
  silentLogIn(){
    var resolves, rejects;

    const emitter = new EventEmitter();

    const promise = new Promise((resolve, reject) => {
      resolves = resolve;
      rejects = reject;
    });

    console.log("Starting silent sign in with google");

    //if (this.platform.is("android")){
      this.googlePlus.trySilentLogin({
        'webClientId': '615463500983-mdif2mnma26qrar8arpcnj271eb9v8r2.apps.googleusercontent.com',
        'offline': false
      }).then((obj) => {
        this.afAuth.signInWithCredential(firebase.auth.GoogleAuthProvider.credential(obj))
          .then((result) => {
            // This gives you a Google Access Token. You can use it to access the Google API.
            var token = result.credential;
            // The signed-in user info.
            var user = result.user;
            //this.authService.setUser(user);
            this.afAuth.updateCurrentUser(user);
            console.log("Signed in user= " + user.displayName + " token= " + token.providerId);
            resolves(result.user);
          })
          .catch((gplusErr) => {
            rejects("GooglePlus failed error= "+gplusErr);
          });
    }).catch( (msg) => {
        rejects("Gplus signin failed error=" + msg);
      });
    return promise; 
  }
  signInGoogle(){
    this.asyncSignInGoogle().then(
        (success : firebase.User) => {
          console.log("Login succesfull");
          console.log(success);
         // this.authService.setUser(success);
         // this.afAuth.updateCurrentUser(success);
          this.router.navigateByUrl("/handle-bracelets");
        },
        (reject => {
          console.log("Login rejected");
          console.log(reject);
        })
    )
  }
  asyncSignInGoogle(){

    var resolves, rejects;

    const emitter = new EventEmitter();

    const promise = new Promise((resolve, reject) => {
      resolves = resolve;
      rejects = reject;
    });
    console.log("Starting to sign in with google");
    var tryDesktop: boolean = false;

    //if (this.platform.is("android")){
      this.googlePlus.login({
        'webClientId': '615463500983-mdif2mnma26qrar8arpcnj271eb9v8r2.apps.googleusercontent.com',
        'offline': true
      }).then((obj) => {
        
        this.afAuth.signInWithCredential(firebase.auth.GoogleAuthProvider.credential(obj))
          .then((result) => {
            // This gives you a Google Access Token. You can use it to access the Google API.
            var token = result.credential;
            // The signed-in user info.
            var user = result.user;
            //this.authService.setUser(user);
            //this.afAuth.updateCurrentUser(user);
            console.log("Signed in user= " + user.displayName + " token= " + token.providerId);
            resolves(result.user);
          })
          .catch((gplusErr) => {
            console.log("GooglePlus failed error= "+gplusErr);
             // we will try desktop mode
            tryDesktop = true;
            console.log("runing in desktop");

            var provider = new auth.GoogleAuthProvider();

            this.afAuth.signInWithPopup(provider).then(function(result) {
              // This gives you a Google Access Token. You can use it to access the Google API.
              var token = result.credential;
              // The signed-in user info.
              var user = result.user;
              //this.authService.setUser(user);
              //this.afAuth.updateCurrentUser(user);
              console.log("Signed in user= " + user.displayName + " token= " + token.providerId);
              resolves(user);
              // ...
            }).catch(function(error) {

              // Handle Errors here.
              var errorCode = error.code;
              var errorMessage = error.message;
              // The email of the user's account used.
              var email = error.email;
              // The firebase.auth.AuthCredential type that was used.
              var credential = error.credential;
              
              rejects("Error in login = " + errorCode + " " + errorMessage);
            });
          
          });
        
    }).catch( (msg) => {
        console.log("Gplus signin failed error=" + msg);
        
        // we will try desktop mode
        tryDesktop = true;

        console.log("runing in desktop");

        var provider = new auth.GoogleAuthProvider();

        this.afAuth.signInWithPopup(provider).then(function(result) {
          // This gives you a Google Access Token. You can use it to access the Google API.
          var token = result.credential;
          // The signed-in user info.
          var user = result.user;
          //this.authService.setUser(user);
          //this.afAuth.updateCurrentUser(user);
          console.log("Signed in user= " + user.displayName + " token= " + token.providerId);
          resolves(user);
          // ...
        }).catch(function(error) {

          // Handle Errors here.
          var errorCode = error.code;
          var errorMessage = error.message;
          // The email of the user's account used.
          var email = error.email;
          // The firebase.auth.AuthCredential type that was used.
          var credential = error.credential;
          // ...
          rejects("Error in login = " + errorCode + " " + errorMessage);
        });

      });

    return promise; 
  }
}
