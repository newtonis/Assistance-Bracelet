'use strict';

Object.defineProperty(exports, '__esModule', { value: true });

var tslib = require('tslib');
var core$1 = require('@angular/core');
var core = require('@ionic-native/core');
require('rxjs');

var FirebaseAuthentication = /** @class */ (function (_super) {
    tslib.__extends(FirebaseAuthentication, _super);
    function FirebaseAuthentication() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    FirebaseAuthentication.prototype.getIdToken = function (forceRefresh) { return core.cordova(this, "getIdToken", { "sync": true }, arguments); };
    FirebaseAuthentication.prototype.createUserWithEmailAndPassword = function (email, password) { return core.cordova(this, "createUserWithEmailAndPassword", { "sync": true }, arguments); };
    FirebaseAuthentication.prototype.sendEmailVerification = function () { return core.cordova(this, "sendEmailVerification", { "sync": true }, arguments); };
    FirebaseAuthentication.prototype.sendPasswordResetEmail = function (email) { return core.cordova(this, "sendPasswordResetEmail", { "sync": true }, arguments); };
    FirebaseAuthentication.prototype.signInWithEmailAndPassword = function (email, password) { return core.cordova(this, "signInWithEmailAndPassword", { "sync": true }, arguments); };
    FirebaseAuthentication.prototype.verifyPhoneNumber = function (phoneNumber, timeout) { return core.cordova(this, "verifyPhoneNumber", { "sync": true }, arguments); };
    FirebaseAuthentication.prototype.signInWithVerificationId = function (verificationId, smsCode) { return core.cordova(this, "signInWithVerificationId", { "sync": true }, arguments); };
    FirebaseAuthentication.prototype.signInAnonymously = function () { return core.cordova(this, "signInAnonymously", { "sync": true }, arguments); };
    FirebaseAuthentication.prototype.signInWithGoogle = function (idToken, accessToken) { return core.cordova(this, "signInWithGoogle", { "sync": true }, arguments); };
    FirebaseAuthentication.prototype.signInWithApple = function (identityToken, rawNonce) { return core.cordova(this, "signInWithApple", { "sync": true }, arguments); };
    FirebaseAuthentication.prototype.signInWithFacebook = function (accessToken) { return core.cordova(this, "signInWithFacebook", { "sync": true }, arguments); };
    FirebaseAuthentication.prototype.signInWithTwitter = function (token, secret) { return core.cordova(this, "signInWithTwitter", { "sync": true }, arguments); };
    FirebaseAuthentication.prototype.onAuthStateChanged = function () { return core.cordova(this, "onAuthStateChanged", { "observable": true, "callbackOrder": "reverse" }, arguments); };
    FirebaseAuthentication.prototype.setLanguageCode = function (languageCode) { return core.cordova(this, "setLanguageCode", { "sync": true }, arguments); };
    FirebaseAuthentication.prototype.useAppLanguage = function () { return core.cordova(this, "useAppLanguage", { "sync": true }, arguments); };
    FirebaseAuthentication.prototype.signOut = function () { return core.cordova(this, "signOut", { "sync": true }, arguments); };
    FirebaseAuthentication.pluginName = "FirebaseAuthentication";
    FirebaseAuthentication.plugin = "cordova-plugin-firebase-authentication";
    FirebaseAuthentication.pluginRef = "cordova.plugins.firebase.auth";
    FirebaseAuthentication.repo = "https://github.com/chemerisuk/cordova-plugin-firebase-authentication";
    FirebaseAuthentication.install = "ionic cordova plugin add cordova-plugin-firebase-authentication --variable FIREBASE_AUTH_VERSION=version";
    FirebaseAuthentication.installVariables = ["FIREBASE_AUTH_VERSION"];
    FirebaseAuthentication.platforms = ["Android", "iOS"];
    FirebaseAuthentication.decorators = [
        { type: core$1.Injectable }
    ];
    return FirebaseAuthentication;
}(core.IonicNativePlugin));

exports.FirebaseAuthentication = FirebaseAuthentication;
