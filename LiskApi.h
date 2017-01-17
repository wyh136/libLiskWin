//---------------------------------------------------------------------------

#ifndef LiskApiH
#define LiskApiH
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
//MADE BY PHINX
//---------------------------------------------------------------------------
//-H "Content-Type: application/json"
typedef enum _REQUEST_METHOD{RGET=1,RPOST=2,RPUT=3}REQUEST_METHOD;
class LiskAPI
{
	private:
			TIdHTTP *http;
            TEncoding *encoding;

			UnicodeString __fastcall _request(REQUEST_METHOD request_method,UnicodeString url,TStrings *data);
            UnicodeString __fastcall _request(UnicodeString url /*GET only*/);
	public:
			__fastcall LiskAPI(UnicodeString nodeurl);
			__fastcall LiskAPI();
			__fastcall ~LiskAPI();
			UnicodeString lisknode;
			UnicodeString __fastcall GetAccountBySecret(UnicodeString secret);   //  /api/accounts/open                    post
			UnicodeString __fastcall Balance(UnicodeString address);  //  /api/accounts/getBalance?address=<address>   	   get
			UnicodeString __fastcall PublicKey(UnicodeString address);//  /api/accounts/getPublicKey?address=address   	   get
			UnicodeString __fastcall GenPublicKey(UnicodeString secret);// /api/accounts/generatePublicKey             	   post
			UnicodeString __fastcall GetAccountByAddress(UnicodeString address);//  /api/accounts?address=address          get
			UnicodeString __fastcall GetDelegates(UnicodeString address);       ///api/accounts/delegates?address=address  get
			UnicodeString __fastcall DelegatesVote(UnicodeString secret,UnicodeString second_secret,UnicodeString pubkey,TStringList *delegates); // /api/accounts/delegates
			//----------------------------------------------finished 2017 1.11-----------------------------------------------------------------
			UnicodeString __fastcall Status();                                  // /api/loader/status   get
			UnicodeString __fastcall SyncStatus();                              //  GET /api/loader/status/sync
			UnicodeString __fastcall Ping();                                    //  /api/loader/status/ping
			//GET /api/transactions?blockId=blockId&senderId=senderId&recipientId=recipientId&limit=limit&offset=offset&orderBy=field
			UnicodeString __fastcall Transactions(UnicodeString blockID,UnicodeString senderId,UnicodeString recvID,__int64 limit,__int64 offset,UnicodeString orderby);
			//PUT /api/transactions
			UnicodeString __fastcall SendTransactions(UnicodeString secret,__int64 amount,UnicodeString recverID,UnicodeString publicKey,UnicodeString secondSecret);
			//GET /api/transactions/get?id=id
			UnicodeString __fastcall GetTransactions(UnicodeString txid);
			//GET /api/transactions/unconfirmed/get?id=id
			UnicodeString __fastcall GetUnConfirmedTxByID(UnicodeString txid);
			//GET /api/transactions/unconfirmed
			UnicodeString __fastcall GetUnConfirmedTx();
			//GET /api/transactions/queued
			UnicodeString __fastcall GetQueuedTx();
			//GET /api/transactions/queued/get?id=id
			UnicodeString __fastcall GetQueuedTxByID(UnicodeString txid);
			//----------------------------------------------------------------------------------------------------------------------
			//GET /api/peers?state=state&os=os&version=version&limit=limit&offset=offset&orderBy=orderBy
			UnicodeString __fastcall GetPeers(UnicodeString state/*1 - disconnected. 2 - connected. 0 - banned*/,UnicodeString os,UnicodeString version,int limit,__int32 offset,UnicodeString orderBy);
			//GET /api/peers/get?ip=ip&port=port
			UnicodeString __fastcall GetPeerByIPEndPoint(UnicodeString ip,int port);
			//GET /api/peers/version
			UnicodeString __fastcall GetVersion();
			//GET /api/blocks/get?id=id
			UnicodeString __fastcall GetBlockByID(UnicodeString blockid);
			//GET /api/blocks?generatorPublicKey=generatorPublicKey&height=height&previousBlock=previousBlock&totalAmount=totalAmount&totalFee=totalFee&limit=limit&offset=offset&orderBy=order
			UnicodeString __fastcall GetBlocks(__int64 totalfee,__int64 totalAmount,UnicodeString prevBlock,__int64 height,UnicodeString generatorPubKey,int limit,__int32 offset,UnicodeString orderBy);
			//GET /api/blocks/getFee
			UnicodeString __fastcall GetBlockFee();
			//GET /api/blocks/getFees
			UnicodeString __fastcall GetFees();
			//GET /api/blocks/getReward
			UnicodeString __fastcall GetReward();
			//GET /api/blocks/getSupply
			UnicodeString __fastcall GetSupply();
			//GET /api/blocks/getHeight
			UnicodeString __fastcall GetHeight();
			//GET /api/blocks/getStatus
			UnicodeString __fastcall GetStatus();
			//GET /api/blocks/getNethash
			UnicodeString __fastcall GetNethash();
			//GET /api/blocks/getMilestone
			UnicodeString __fastcall GetMilestone();
			//-----------------------------------------------finished 2017-1-11---------------------------------------------------------------------
			//GET /api/signatures/get?id=id
			UnicodeString __fastcall GetSignatureFee();
			//PUT /api/signatures
			UnicodeString __fastcall AddSignature(UnicodeString secret,UnicodeString secondSecret,UnicodeString publickey);
			//-----------------------------------------------finished 2017-1-16------------------------------------------------------
			//PUT /api/delegates
			UnicodeString __fastcall CreateDelegate(UnicodeString secret,UnicodeString second_secret,UnicodeString username);
			//GET /api/delegates?limit=limit&offset=offset&orderBy=orderBy
			UnicodeString __fastcall DelegatesList(int limit,__int32 offset,UnicodeString orderBy);
			//GET /api/delegates/get?publicKey=publicKey
			UnicodeString __fastcall GetDelegateByPkey(UnicodeString publickey);
			UnicodeString __fastcall GetDelegateByName(UnicodeString username);
			//GET /api/delegates/search?q=username&orderBy=producedblocks:desc
			UnicodeString __fastcall SearchDelegate(UnicodeString username,UnicodeString orderby);
			//GET /api/delegates/count
			UnicodeString __fastcall DelegatesCount();
			//GET /api/accounts/delegates/?address=address
			UnicodeString __fastcall GetVotesByAddress(UnicodeString address);
			//GET /api/delegates/voters?publicKey=publicKey
			UnicodeString __fastcall GetVotersByPubkey(UnicodeString publicKey);
			//POST /api/delegates/forging/enable
			UnicodeString __fastcall EnableForge(UnicodeString secret);
			//POST /api/delegates/forging/disable
			UnicodeString __fastcall DisableForge(UnicodeString secret);
			//GET /api/delegates/forging/getForgedByAccount?generatorPublicKey=generatorPublicKey
			UnicodeString __fastcall GetForgedAmount(UnicodeString pubkey);
			//GET /api/delegates/getNextForgers?limit=limit
			UnicodeString __fastcall GetNextForgers(int limit);
			//-----------------------------------------------finished 2017-1-16----------------------------------------------------
			//PUT /api/dapps
			UnicodeString __fastcall RegistDapp(UnicodeString secret,UnicodeString secondSecret,UnicodeString pubkey,UnicodeString category,UnicodeString name,UnicodeString description,UnicodeString tags,int type,UnicodeString link,UnicodeString icon);
			//GET /api/dapps?category=category&name=name&type=type&link=link&limit=limit&offset=offset&orderBy=orderBy
			UnicodeString __fastcall GetDapps(UnicodeString category,UnicodeString name,int type,UnicodeString link,int limit,__int32 offset,UnicodeString orderBy);
			//GET /api/dapps/get?id=id
			UnicodeString __fastcall GetDapp(UnicodeString id);
			//GET /api/dapps/search?q=q&category=category&installed=installed
			UnicodeString __fastcall SearchDapp(UnicodeString query,UnicodeString category,int isInstalled);
			//POST /api/dapps/install
			UnicodeString __fastcall InstallDapp(UnicodeString id);
			//GET /api/dapps/installed
			UnicodeString __fastcall InstalledDapps();
			//GET /api/dapps/installedIds
			UnicodeString __fastcall InstalledDappIds();
			//POST /api/dapps/uninstall
			UnicodeString __fastcall UninstallDapp(UnicodeString id);
			//POST /api/dapps/launch
			UnicodeString __fastcall LaunchDapp(UnicodeString id,TStringList params);
			//GET /api/dapps/installing
			UnicodeString __fastcall InstallingDapps();
			//GET /api/dapps/uninstalling
			UnicodeString __fastcall UnInstallingDapps();
			//GET /api/dapps/launched
			UnicodeString __fastcall LaunchedDapps();
			//GET /api/dapps/categories
			UnicodeString __fastcall Catefories();
			//POST /api/dapps/stop
			UnicodeString __fastcall StopDapp(UnicodeString id);
			//PUT /api/multisignatures
			UnicodeString __fastcall MultiSign(UnicodeString secret,int lifetime,int min,TStringList *keysgroup);
			//GET /api/multisignatures/accounts?publicKey=publicKey
			UnicodeString __fastcall GetMultiSign(UnicodeString publickey);
			//POST /api/multisignatures/sign
			UnicodeString __fastcall SignMultiSignature(UnicodeString secret,UnicodeString publickey,UnicodeString txid);
			//GET /api/multisignatures/pending?publicKey=publicKey
			UnicodeString __fastcall GetPendingMultiSign(UnicodeString publickey);
};
#endif
