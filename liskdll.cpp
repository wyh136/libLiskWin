// Important note about DLL memory management when your DLL uses the
// static version of the RunTime Library:
//
// If your DLL exports any functions that pass String objects (or structs/
// classes containing nested Strings) as parameter or function results,
// you will need to add the library MEMMGR.LIB to both the DLL project and
// any other projects that use the DLL.  You will also need to use MEMMGR.LIB
// if any other projects which use the DLL will be performing new or delete
// operations on any non-TObject-derived classes which are exported from the
// DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
// EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
// the file BORLNDMM.DLL should be deployed along with your DLL.
//
// To avoid using BORLNDMM.DLL, pass string information using "char *" or
// ShortString parameters.
//
// If your DLL uses the dynamic version of the RTL, you do not need to
// explicitly add MEMMGR.LIB as this will be done implicitly for you

#include <vcl.h>
#include <windows.h>
#include "LiskApi.h"
#pragma hdrstop
#pragma argsused
#define BUILD_DLL
#ifdef BUILD_DLL
#define IMPORT_EXPORT __declspec(dllexport)
#else
#define IMPORT_EXPORT __declspec(dllimport)
#endif
LiskAPI *liskapi = NULL;

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason,
	void* lpReserved) {
	return 1;
}

extern "C" {

	IMPORT_EXPORT  void __stdcall InitAPI(char *nodeurl) {
		if (liskapi == NULL)
			liskapi = new LiskAPI(nodeurl);
	}

	IMPORT_EXPORT  void __stdcall SetNodeURL(char *nodeurl) {
		liskapi->lisknode = AnsiString(nodeurl);
	}

	IMPORT_EXPORT  void __stdcall FreeAPI() {
		if (liskapi != NULL) {
			delete liskapi;
			liskapi = NULL;
		}
	}

	IMPORT_EXPORT  char * __stdcall GetAccountBySecret(char * secret) {
		return liskapi->GetAccountBySecret(secret);
	}

	IMPORT_EXPORT  char * __stdcall Balance(char * address) {
		return liskapi->Balance(address);
	}

	IMPORT_EXPORT  char * __stdcall PublicKey(char * address) {
		return liskapi->PublicKey(address);
	}

	IMPORT_EXPORT  char * __stdcall GenPublicKey(char * secret) {
		return liskapi->GenPublicKey(secret);
	}

	IMPORT_EXPORT  char * __stdcall GetAccountByAddress(char * address) {
		return liskapi->GetAccountByAddress(address);
	}

	IMPORT_EXPORT  char * __stdcall GetDelegates(char * address) {
		return liskapi->GetDelegates(address);
	}

	IMPORT_EXPORT  char * __stdcall DelegatesVote(char * secret,
		char * second_secret, char * pubkey, char *delegates) {
		return liskapi->DelegatesVote(secret, second_secret, pubkey, delegates);
	}

	IMPORT_EXPORT  char * __stdcall Status() {
		return liskapi->Status();
	}

	IMPORT_EXPORT  char * __stdcall SyncStatus() {
		return liskapi->SyncStatus();
	}

	IMPORT_EXPORT  char * __stdcall Ping() {
		return liskapi->Ping();
	}

	IMPORT_EXPORT  char * __stdcall Transations(char * blockID,
		char * senderId, char * recvID, __int64 limit, __int64 offset,
		char * orderby) {
		return liskapi->Transactions(blockID, senderId, recvID, limit, offset,
			orderby);
	}

	IMPORT_EXPORT  char * __stdcall SendTransactions(char * secret,
		__int64 amount, char * recverID, char * publicKey, char * secondSecret)
	{
		return liskapi->SendTransactions(secret, amount, recverID, publicKey,
			secondSecret);
	}

	IMPORT_EXPORT  char * __stdcall GetTransactions(char * txid) {
		return liskapi->GetTransactions(txid);
	}

	IMPORT_EXPORT  char * __stdcall GetUnConfirmedTxByID(char * txid) {
		return liskapi->GetUnConfirmedTxByID(txid);
	}

	IMPORT_EXPORT  char * __stdcall GetUnConfirmedTx() {
		return liskapi->GetUnConfirmedTx();
	}

	IMPORT_EXPORT  char * __stdcall GetQueuedTx() {
		return liskapi->GetQueuedTx();
	}

	IMPORT_EXPORT  char * __stdcall GetQueuedTxByID(char * txid) {
		return liskapi->GetQueuedTxByID(txid);
	}

	IMPORT_EXPORT  char * __stdcall GetPeers(int state, char * os,
		char * version, int limit, __int32 offset, char * orderBy) {
		return liskapi->GetPeers(state, os, version, limit, offset, orderBy);
	}

	IMPORT_EXPORT  char * __stdcall GetPeerByIPEndPoint(char * ip,
		int port) {
		return liskapi->GetPeerByIPEndPoint(ip, port);
	}

	IMPORT_EXPORT  char * __stdcall LiskNodeVersion() {
		return liskapi->LiskNodeVersion();
	}

	IMPORT_EXPORT  char * __stdcall GetBlockByID(char * blockid) {
		return liskapi->GetBlockByID(blockid);
	}

	IMPORT_EXPORT  char * __stdcall GetBlocks(__int64 totalfee,
		__int64 totalAmount, char * prevBlock, __int64 height,
		char * generatorPubKey, int limit, __int32 offset, char * orderBy) {
		return liskapi->GetBlocks(totalfee, totalAmount, prevBlock, height,
			generatorPubKey, limit, offset, orderBy);
	}

	IMPORT_EXPORT  char * __stdcall GetBlockFee() {
		return liskapi->GetBlockFee();
	}

	IMPORT_EXPORT  char * __stdcall GetFees() {
		return liskapi->GetFees();
	}

	IMPORT_EXPORT  char * __stdcall GetReward() {
		return liskapi->GetReward();
	}

	IMPORT_EXPORT  char * __stdcall GetSupply() {
		return liskapi->GetSupply();
	}

	IMPORT_EXPORT  char * __stdcall GetHeight() {
		return liskapi->GetHeight();
	}

	IMPORT_EXPORT  char * __stdcall GetStatus() {
		return liskapi->GetStatus();
	}

	IMPORT_EXPORT  char * __stdcall GetNethash() {
		return liskapi->GetNethash();
	}

	IMPORT_EXPORT  char * __stdcall GetMilestone() {
		return liskapi->GetMilestone();
	}

	IMPORT_EXPORT  char * __stdcall GetSignatureFee() {
		return liskapi->GetSignatureFee();
	}

	IMPORT_EXPORT  char * __stdcall AddSignature(char * secret,
		char * secondSecret, char * publickey) {
		return liskapi->AddSignature(secret, secondSecret, publickey);
	}

	IMPORT_EXPORT  char * __stdcall CreateDelegate(char * secret,
		char * second_secret, char * username) {
		return liskapi->CreateDelegate(secret, second_secret, username);
	}

	IMPORT_EXPORT  char * __stdcall DelegatesList(int limit,
		__int32 offset, char * orderBy) {
		return liskapi->DelegatesList(limit, offset, orderBy);
	}

	IMPORT_EXPORT  char * __stdcall GetDelegateByPkey(char * publickey) {
		return liskapi->GetDelegateByPkey(publickey);
	}

	IMPORT_EXPORT  char * __stdcall GetDelegateByName(char * username) {
		return liskapi->GetDelegateByName(username);
	}

	IMPORT_EXPORT  char * __stdcall SearchDelegate(char * username,
		char * orderby) {
		return liskapi->SearchDelegate(username, orderby);
	}

	IMPORT_EXPORT  char * __stdcall DelegatesCount() {
		return liskapi->DelegatesCount();
	}

	IMPORT_EXPORT  char * __stdcall GetVotesByAddress(char * address) {
		return liskapi->GetVotesByAddress(address);
	}

	IMPORT_EXPORT  char * __stdcall GetVotersByPubkey(char * publicKey) {
		return liskapi->GetVotersByPubkey(publicKey);
	}

	IMPORT_EXPORT  char * __stdcall EnableForge(char * secret) {
		return liskapi->EnableForge(secret);
	}

	IMPORT_EXPORT  char * __stdcall DisableForge(char * secret) {
		return liskapi->DisableForge(secret);
	}

	IMPORT_EXPORT  char * __stdcall GetForgedAmount(char * pubkey) {
		return liskapi->GetForgedAmount(pubkey);
	}

	IMPORT_EXPORT  char * __stdcall GetNextForgers(int limit) {
		return liskapi->GetNextForgers(limit);
	}

	IMPORT_EXPORT  char * __stdcall RegistDapp(char * secret,
		char * secondSecret, char * pubkey, char * category, char * name,
		char * description, char * tags, int type, char * link, char * icon) {
		return liskapi->RegistDapp(secret, secondSecret, pubkey, category, name,
			description, tags, type, link, icon);
	}

	IMPORT_EXPORT  char * __stdcall GetDapps(char * category,
		char * name, int type, char * link, int limit, __int32 offset,
		char * orderBy) {
		return liskapi->GetDapps(category, name, type, link, limit, offset,
			orderBy);
	}

	IMPORT_EXPORT  char * __stdcall GetDapp(char * id) {
		return liskapi->GetDapp(id);
	}

	IMPORT_EXPORT  char * __stdcall SearchDapp(char * query,
		char * category, int isInstalled) {
		return liskapi->SearchDapp(query, category, isInstalled);
	}

	IMPORT_EXPORT  char * __stdcall InstallDapp(char * id) {
		return liskapi->InstallDapp(id);
	}

	IMPORT_EXPORT  char * __stdcall InstalledDapps() {
		return liskapi->InstalledDapps();
	}

	IMPORT_EXPORT  char * __stdcall InstalledDappIds() {
		return liskapi->InstalledDappIds();
	}

	IMPORT_EXPORT  char * __stdcall UninstallDapp(char * id) {
		return liskapi->UninstallDapp(id);
	}

	IMPORT_EXPORT  char * __stdcall LaunchDapp(char * id, char * params)
	{
		return liskapi->LaunchDapp(id, params);
	}

	IMPORT_EXPORT  char * __stdcall InstallingDapps() {
		return liskapi->InstallingDapps();
	}

	IMPORT_EXPORT  char * __stdcall UnInstallingDapps() {
		return liskapi->UnInstallingDapps();
	}

	IMPORT_EXPORT  char * __stdcall LaunchedDapps() {
		return liskapi->LaunchedDapps();
	}

	IMPORT_EXPORT  char * __stdcall Catefories() {
		return liskapi->Catefories();
	}

	IMPORT_EXPORT  char * __stdcall StopDapp(char * id) {
		return liskapi->StopDapp(id);
	}

	IMPORT_EXPORT  char * __stdcall MultiSign(char * secret,
		int lifetime, int min, char *keysgroup) {
		return liskapi->MultiSign(secret, lifetime, min, keysgroup);
	}

	IMPORT_EXPORT  char * __stdcall GetMultiSign(char * publickey) {
		return liskapi->GetMultiSign(publickey);
	}

	IMPORT_EXPORT  char * __stdcall SignMultiSignature(char * secret,
		char * publickey, char * txid) {
		return liskapi->SignMultiSignature(secret, publickey, txid);
	}

	IMPORT_EXPORT  char * __stdcall GetPendingMultiSign(char * publickey)
	{
		return liskapi->GetPendingMultiSign(publickey);
	}

	IMPORT_EXPORT char * __stdcall HTTPRequest(int request_method,char * url,char *data)
	{
		return liskapi->HTTPRequest((REQUEST_METHOD)request_method,url,data);
	}
}
