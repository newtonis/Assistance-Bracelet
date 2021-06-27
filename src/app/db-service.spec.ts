import { AngularFireDatabase } from '@angular/fire/database';
import { DbServiceService } from './db-service.service';

describe('MasterService without Angular testing support', () => {
    let dbService: DbServiceService;
  
    it('#getValue should return real value from the real service', () => {
        dbService = new DbServiceService(new ValueService());
      expect(dbService.getBraceletData());
    });
  
});