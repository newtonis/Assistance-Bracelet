import { Injectable } from '@angular/core';

import { Observable, BehaviorSubject, ReplaySubject } from 'rxjs';
import { AngularFireAuth } from '@angular/fire/auth';
import { AngularFireDatabase, AngularFireList, AngularFireObject } from '@angular/fire/database';
import { Bracelet, generateBracelet } from './types';
import EventEmitter from 'events';

@Injectable({
  providedIn: 'root'
})
export class DbServiceService {
  braceletDataRef: AngularFireList<Bracelet>;
  braceletData: AngularFireList<Bracelet>;

  braceletBehaviour: BehaviorSubject<Bracelet[]>;
  
  constructor(private afd: AngularFireDatabase) {
    this.braceletBehaviour = new BehaviorSubject([]);
  }

  askForBraceletData(userId: string){
    console.log(`Getting '${userId}' data`);

    this.braceletDataRef = this.afd.list<Bracelet>(`Bracelets/${userId}`);
    
    this.braceletDataRef.valueChanges().subscribe((data : Bracelet[]) => {
      var dataFiltered: Bracelet[] = data.filter(function(item: Bracelet){
        return item.valid;
      });

      this.braceletBehaviour.next(dataFiltered);
    });
  }
  getBraceletObs() : Observable<Bracelet[]>{
    return this.braceletBehaviour.asObservable();
  }
  /*loadMedicine() : Medicine{

    return null;
  }*/
  loadUser(){

  }
  loadBracelet(){

  }
  addBracelet(
    surname: string,
    firstname: string,
    lastname: string,
    birthday: number,
    userId: string
  ) : Promise <any>{
    var resolves, rejects;

    const emitter = new EventEmitter();

    const promise = new Promise((resolve, reject) => {
      resolves = resolve;
      rejects = reject;
    });

    this.braceletDataRef = this.afd.list<Bracelet>(`Bracelets/${userId}`);

    this.braceletDataRef.push(
      generateBracelet(
        firstname,
        lastname,
        surname,
        birthday
      )
    ).then(function(){
      resolves(true);
    }).catch(function(){
      console.log("Error writting data");
    });

    return promise;
  }
}
