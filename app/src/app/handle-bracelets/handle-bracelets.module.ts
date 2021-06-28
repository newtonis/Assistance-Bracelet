import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { HandleBraceletsPageRoutingModule } from './handle-bracelets-routing.module';

import { HandleBraceletsPage } from './handle-bracelets.page';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    HandleBraceletsPageRoutingModule
  ],
  declarations: [HandleBraceletsPage]
})
export class HandleBraceletsPageModule {}
