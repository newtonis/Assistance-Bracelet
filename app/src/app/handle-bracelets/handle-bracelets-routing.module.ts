import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { HandleBraceletsPage } from './handle-bracelets.page';

const routes: Routes = [
  {
    path: '',
    component: HandleBraceletsPage
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
})
export class HandleBraceletsPageRoutingModule {}
