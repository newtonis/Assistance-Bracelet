import { NgModule } from '@angular/core';
import { PreloadAllModules, RouterModule, Routes } from '@angular/router';

const routes: Routes = [
  {
    path: 'home',
    loadChildren: () => import('./home/home.module').then( m => m.HomePageModule)
  },
  {
    path: '',
    redirectTo: 'login',
    pathMatch: 'full'
  },
  {
    path: 'login',
    loadChildren: () => import('./login/login.module').then( m => m.LoginPageModule)
  },
  {
    path: 'welcome-user',
    loadChildren: () => import('./welcome-user/welcome-user.module').then( m => m.WelcomeUserPageModule)
  },
  {
    path: 'handle-bracelets',
    loadChildren: () => import('./handle-bracelets/handle-bracelets.module').then( m => m.HandleBraceletsPageModule)
  },  {
    path: 'new-bracelet',
    loadChildren: () => import('./new-bracelet/new-bracelet.module').then( m => m.NewBraceletPageModule)
  },

];

@NgModule({
  imports: [
    RouterModule.forRoot(routes, { preloadingStrategy: PreloadAllModules })
  ],
  exports: [RouterModule]
})
export class AppRoutingModule { }
