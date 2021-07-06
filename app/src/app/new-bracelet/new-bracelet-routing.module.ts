import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Routes, RouterModule } from '@angular/router';

import { NewBraceletPage } from './new-bracelet.page';

const routes: Routes = [
  {
    path: '',
    component: NewBraceletPage
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes), FormsModule],
  exports: [RouterModule],
})
export class NewBraceletPageRoutingModule {}
