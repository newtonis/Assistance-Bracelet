import { Injectable } from '@angular/core';

import { Observable, BehaviorSubject } from 'rxjs';
import { AngularFireAuth } from '@angular/fire/auth';
import { AngularFireDatabase, AngularFireList, AngularFireObject } from '@angular/fire/database';
import { Bracelet } from './types';


@Injectable({
  providedIn: 'root'
})
export class DbServiceService {
  braceletDataRef: AngularFireList<Bracelet>;
  braceletData: AngularFireList<Bracelet>;

  

  constructor(private afd: AngularFireDatabase) {
    
  }
  startDataInterface(){
    this.braceletDataRef = this.afd.list<Bracelet>(`Bracelets/`);
    
    this.braceletDataRef.valueChanges().subscribe(data => {
      ;
    });
  
  
  }
  /*loadMedicine() : Medicine{

    return null;
  }*/
  loadUser(){

  }
  loadBracelet(){

  }
  addBracelet(){

  }

}
