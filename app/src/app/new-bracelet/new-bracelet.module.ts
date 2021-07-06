import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { NewBraceletPageRoutingModule } from './new-bracelet-routing.module';

import { NewBraceletPage } from './new-bracelet.page';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    NewBraceletPageRoutingModule
  ],
  declarations: [NewBraceletPage]
})
export class NewBraceletPageModule {}
