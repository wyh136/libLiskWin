//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you

#include <vcl.h>
#include <windows.h>
#include "LiskApi.h"
#pragma hdrstop
#pragma argsused
LiskAPI *liskapi=NULL;
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	return 1;
}
extern "C" __declspec(dllexport) void __stdcall InitAPI()
{
	if(liskapi==NULL)liskapi=new LiskAPI();
}
extern "C" __declspec(dllexport) void __stdcall SetNodeURL(char *nodeurl)
{
	InitAPI();
    liskapi->lisknode=AnsiString(nodeurl);
}
extern "C" __declspec(dllexport) void __stdcall FreeAPI()
{
	if(liskapi!=NULL){delete liskapi;liskapi=NULL;}
}
extern "C" __declspec(dllexport) char * __stdcall GetAccountBySecret(char * secret)
{
	 return liskapi->GetAccountBySecret(secret);
}

extern "C" __declspec(dllexport) char * __stdcall Balance(char * address)
{
	 return liskapi->Balance(address);
}
extern "C" __declspec(dllexport) char * __stdcall PublicKey(char * address)
{
   return liskapi->PublicKey(address);
}
extern "C" __declspec(dllexport) char * __stdcall GenPublicKey(char * secret)
{
   return liskapi->GenPublicKey(secret);
}
extern "C" __declspec(dllexport) char * __stdcall GetAccountByAddress(char * address)
{
	return liskapi->GetAccountByAddress(address);
}
extern "C" __declspec(dllexport) char * __stdcall GetDelegates(char * address)
{
   return liskapi->GetDelegates(address);
}
extern "C" __declspec(dllexport) char * __stdcall DelegatesVote(char * secret,char * second_secret,char * pubkey,char *delegates)
{
   return liskapi->DelegatesVote(secret,second_secret,pubkey,delegates);
}
extern "C" __declspec(dllexport) char * __stdcall Status()
{
   return liskapi->Status();
}
extern "C" __declspec(dllexport) char * __stdcall SyncStatus()
{
   return liskapi->SyncStatus();
}
extern "C" __declspec(dllexport) char * __stdcall Ping()
{
   return liskapi->Ping();
}
extern "C" __declspec(dllexport) char * __stdcall Transations(char * blockID,char * senderId,char * recvID,__int64 limit,__int64 offset,char * orderby)
{
   return liskapi->Transactions(blockID,senderId,recvID,limit,offset,orderby);
}
extern "C" __declspec(dllexport) char * __stdcall SendTransactions(char * secret,__int64 amount,char * recverID,char * publicKey,char * secondSecret)
{
   return liskapi->SendTransactions(secret,amount,recverID,publicKey,secondSecret);
}
extern "C" __declspec(dllexport) char * __stdcall GetTransactions(char * txid)
{
   return liskapi->GetTransactions(txid);
}
extern "C" __declspec(dllexport) char * __stdcall GetUnConfirmedTxByID(char * txid)
{
   return liskapi->GetUnConfirmedTxByID(txid);
}
extern "C" __declspec(dllexport) char * __stdcall GetUnConfirmedTx()
{
   return liskapi->GetUnConfirmedTx();
}
extern "C" __declspec(dllexport) char * __stdcall GetQueuedTx()
{
   return liskapi->GetQueuedTx();
}
extern "C" __declspec(dllexport) char * __stdcall GetQueuedTxByID(char * txid)
{
   return liskapi->GetQueuedTxByID(txid);
}
extern "C" __declspec(dllexport) char * __stdcall GetPeers(int state,char * os,char * version,int limit,__int32 offset,char * orderBy)
{
   return liskapi->GetPeers(state, os, version, limit, offset, orderBy);
}
extern "C" __declspec(dllexport) char * __stdcall GetPeerByIPEndPoint(char * ip,int port)
{
   return liskapi->GetPeerByIPEndPoint( ip,port);
}
extern "C" __declspec(dllexport) char * __stdcall LisNodeVersion()
{
   return liskapi->LisNodeVersion();
}
extern "C" __declspec(dllexport) char * __stdcall GetBlockByID(char * blockid)
{
   return liskapi->GetBlockByID(blockid);
}
extern "C" __declspec(dllexport) char * __stdcall GetBlocks(__int64 totalfee,__int64 totalAmount,char * prevBlock,__int64 height,char * generatorPubKey,int limit,__int32 offset,char * orderBy)
{
   return liskapi->GetBlocks(totalfee,totalAmount, prevBlock,height, generatorPubKey,limit,offset,orderBy);
}
extern "C" __declspec(dllexport) char * __stdcall GetBlockFee()
{
   return liskapi->GetBlockFee();
}
extern "C" __declspec(dllexport) char * __stdcall GetFees()
{
   return liskapi->GetFees();
}
extern "C" __declspec(dllexport) char * __stdcall GetReward()
{
   return liskapi->GetReward();
}
extern "C" __declspec(dllexport) char * __stdcall GetSupply()
{
   return liskapi->GetSupply();
}
extern "C" __declspec(dllexport) char * __stdcall GetHeight()
{
   return liskapi->GetHeight();
}
extern "C" __declspec(dllexport) char * __stdcall GetStatus()
{
   return liskapi->GetStatus();
}
extern "C" __declspec(dllexport) char * __stdcall GetNethash()
{
   return liskapi->GetNethash();
}
extern "C" __declspec(dllexport) char * __stdcall GetMilestone()
{
   return liskapi->GetMilestone();
}
extern "C" __declspec(dllexport) char * __stdcall GetSignatureFee()
{
   return liskapi->GetSignatureFee();
}
extern "C" __declspec(dllexport) char * __stdcall AddSignature(char * secret,char * secondSecret,char * publickey)
{
   return liskapi->AddSignature( secret, secondSecret, publickey);
}
extern "C" __declspec(dllexport) char * __stdcall CreateDelegate(char * secret,char * second_secret,char * username)
{
   return liskapi->CreateDelegate( secret, second_secret, username);
}
extern "C" __declspec(dllexport) char * __stdcall DelegatesList(int limit,__int32 offset,char * orderBy)
{
	return liskapi->DelegatesList(limit,offset,orderBy);
}
extern "C" __declspec(dllexport) char * __stdcall GetDelegateByPkey(char * publickey)
{
	return liskapi->GetDelegateByPkey(publickey);
}
extern "C" __declspec(dllexport) char * __stdcall GetDelegateByName(char * username)
{
	return liskapi->GetDelegateByName(username);
}
extern "C" __declspec(dllexport) char * __stdcall SearchDelegate(char * username,char * orderby)
{
	return liskapi->SearchDelegate( username, orderby);
}
extern "C" __declspec(dllexport) char * __stdcall DelegatesCount()
{
	return liskapi->DelegatesCount();
}
extern "C" __declspec(dllexport) char * __stdcall GetVotesByAddress(char * address)
{
	return liskapi->GetVotesByAddress(address);
}
extern "C" __declspec(dllexport) char * __stdcall GetVotersByPubkey(char * publicKey)
{
	return liskapi->GetVotersByPubkey(publicKey);
}
extern "C" __declspec(dllexport) char * __stdcall EnableForge(char * secret)
{
	return liskapi->EnableForge(secret);
}
extern "C" __declspec(dllexport) char * __stdcall DisableForge(char * secret)
{
	return liskapi->DisableForge(secret);
}
extern "C" __declspec(dllexport) char * __stdcall GetForgedAmount(char * pubkey)
{
	return liskapi->GetForgedAmount(pubkey);
}
extern "C" __declspec(dllexport) char * __stdcall GetNextForgers(int limit)
{
	return liskapi->GetNextForgers(limit);
}
extern "C" __declspec(dllexport) char * __stdcall RegistDapp(char * secret,char * secondSecret,char * pubkey,char * category,char * name,char * description,char * tags,int type,char * link,char * icon)
{
	return liskapi->RegistDapp( secret, secondSecret, pubkey, category, name, description, tags, type, link, icon);
}
extern "C" __declspec(dllexport) char * __stdcall GetDapps(char * category,char * name,int type,char * link,int limit,__int32 offset,char * orderBy)
{
	return liskapi->GetDapps( category, name, type, link, limit, offset, orderBy);
}
extern "C" __declspec(dllexport) char * __stdcall GetDapp(char * id)
{
	return liskapi->GetDapp(id);
}
extern "C" __declspec(dllexport) char * __stdcall SearchDapp(char * query,char * category,int isInstalled)
{
	return liskapi->SearchDapp(query, category,isInstalled);
}
extern "C" __declspec(dllexport) char * __stdcall InstallDapp(char * id)
{
	return liskapi->InstallDapp(id);
}
extern "C" __declspec(dllexport) char * __stdcall InstalledDapps()
{
	return liskapi->InstalledDapps();
}
extern "C" __declspec(dllexport) char * __stdcall InstalledDappIds()
{
	return liskapi->InstalledDappIds();
}
extern "C" __declspec(dllexport) char * __stdcall UninstallDapp(char * id)
{
	return liskapi->UninstallDapp(id);
}
extern "C" __declspec(dllexport) char * __stdcall LaunchDapp(char * id,char * params)
{
	return liskapi->LaunchDapp(id,params);
}
extern "C" __declspec(dllexport) char * __stdcall InstallingDapps()
{
	return liskapi->InstallingDapps();
}
extern "C" __declspec(dllexport) char * __stdcall UnInstallingDapps()
{
	return liskapi->UnInstallingDapps();
}
extern "C" __declspec(dllexport) char * __stdcall LaunchedDapps()
{
	return liskapi->LaunchedDapps();
}
extern "C" __declspec(dllexport) char * __stdcall Catefories()
{
	return liskapi->Catefories();
}
extern "C" __declspec(dllexport) char * __stdcall StopDapp(char * id)
{
	return liskapi->StopDapp(id);
}
extern "C" __declspec(dllexport) char * __stdcall MultiSign(char * secret,int lifetime,int min,char *keysgroup)
{
	return liskapi->MultiSign(secret,lifetime,min,keysgroup);
}
extern "C" __declspec(dllexport) char * __stdcall GetMultiSign(char * publickey)
{
	return liskapi->GetMultiSign(publickey);
}
extern "C" __declspec(dllexport) char * __stdcall SignMultiSignature(char * secret,char * publickey,char * txid)
{
	return liskapi->SignMultiSignature( secret, publickey, txid);
}
extern "C" __declspec(dllexport) char * __stdcall GetPendingMultiSign(char * publickey)
{
   return liskapi->GetPendingMultiSign(publickey);
}
