//---------------------------------------------------------------------------
#ifndef LiskApiH
#define LiskApiH
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
//MADE BY PHINX
//---------------------------------------------------------------------------
//-H "Content-Type: application/json"
typedef enum _REQUEST_METHOD{RGET=1,RPOST=2,RPUT=3}REQUEST_METHOD;
class LiskAPI
{
	private:
			TIdHTTP *http;
            TIdSSLIOHandlerSocketOpenSSL *ssl;
			TEncoding *encoding;
			char * __stdcall _request(REQUEST_METHOD request_method,char * url,char *data);
			char * __stdcall _request(char * url /*GET only*/);
	public:
			__stdcall LiskAPI(char * nodeurl);
			__stdcall LiskAPI();
			__stdcall ~LiskAPI();
			AnsiString lisknode;
            char * __stdcall HTTPRequest(REQUEST_METHOD request_method,char * url,char *data);
			char * __stdcall GetAccountBySecret(char * secret);   //  /api/accounts/open                    post
			char * __stdcall Balance(char * address);  //  /api/accounts/getBalance?address=<address>   	   get
			char * __stdcall PublicKey(char * address);//  /api/accounts/getPublicKey?address=address   	   get
			char * __stdcall GenPublicKey(char * secret);// /api/accounts/generatePublicKey             	   post
			char * __stdcall GetAccountByAddress(char * address);//  /api/accounts?address=address          get
			char * __stdcall GetDelegates(char * address);       ///api/accounts/delegates?address=address  get
			char * __stdcall DelegatesVote(char * secret,char * second_secret,char * pubkey,char *delegates); // /api/accounts/delegates
			//----------------------------------------------finished 2017 1.11-----------------------------------------------------------------
			char * __stdcall Status();                                  // /api/loader/status   get
			char * __stdcall SyncStatus();                              //  GET /api/loader/status/sync
			char * __stdcall Ping();                                    //  /api/loader/status/ping
			//GET /api/transactions?blockId=blockId&senderId=senderId&recipientId=recipientId&limit=limit&offset=offset&orderBy=field
			char * __stdcall Transactions(char * blockID,char * senderId,char * recvID,__int64 limit,__int64 offset,char * orderby);
			//PUT /api/transactions
			char * __stdcall SendTransactions(char * secret,__int64 amount,char * recverID,char * publicKey,char * secondSecret);
			//GET /api/transactions/get?id=id
			char * __stdcall GetTransactions(char * txid);
			//GET /api/transactions/unconfirmed/get?id=id
			char * __stdcall GetUnConfirmedTxByID(char * txid);
			//GET /api/transactions/unconfirmed
			char * __stdcall GetUnConfirmedTx();
			//GET /api/transactions/queued
			char * __stdcall GetQueuedTx();
			//GET /api/transactions/queued/get?id=id
			char * __stdcall GetQueuedTxByID(char * txid);
			//----------------------------------------------------------------------------------------------------------------------
			//GET /api/peers?state=state&os=os&version=version&limit=limit&offset=offset&orderBy=orderBy
			char * __stdcall GetPeers(int state/*1 - disconnected. 2 - connected. 0 - banned*/,char * os,char * version,int limit,__int32 offset,char * orderBy);
			//GET /api/peers/get?ip=ip&port=port
			char * __stdcall GetPeerByIPEndPoint(char * ip,int port);
			//GET /api/peers/version
			char * __stdcall LiskNodeVersion();
			//GET /api/blocks/get?id=id
			char * __stdcall GetBlockByID(char * blockid);
			//GET /api/blocks?generatorPublicKey=generatorPublicKey&height=height&previousBlock=previousBlock&totalAmount=totalAmount&totalFee=totalFee&limit=limit&offset=offset&orderBy=order
			char * __stdcall GetBlocks(__int64 totalfee,__int64 totalAmount,char * prevBlock,__int64 height,char * generatorPubKey,int limit,__int32 offset,char * orderBy);
			//GET /api/blocks/getFee
			char * __stdcall GetBlockFee();
			//GET /api/blocks/getFees
			char * __stdcall GetFees();
			//GET /api/blocks/getReward
			char * __stdcall GetReward();
			//GET /api/blocks/getSupply
			char * __stdcall GetSupply();
			//GET /api/blocks/getHeight
			char * __stdcall GetHeight();
			//GET /api/blocks/getStatus
			char * __stdcall GetStatus();
			//GET /api/blocks/getNethash
			char * __stdcall GetNethash();
			//GET /api/blocks/getMilestone
			char * __stdcall GetMilestone();
			//-----------------------------------------------finished 2017-1-11---------------------------------------------------------------------
			//GET /api/signatures/get?id=id
			char * __stdcall GetSignatureFee();
			//PUT /api/signatures
			char * __stdcall AddSignature(char * secret,char * secondSecret,char * publickey);
			//-----------------------------------------------finished 2017-1-16------------------------------------------------------
			//PUT /api/delegates
			char * __stdcall CreateDelegate(char * secret,char * second_secret,char * username);
			//GET /api/delegates?limit=limit&offset=offset&orderBy=orderBy
			char * __stdcall DelegatesList(int limit,__int32 offset,char * orderBy);
			//GET /api/delegates/get?publicKey=publicKey
			char * __stdcall GetDelegateByPkey(char * publickey);
			char * __stdcall GetDelegateByName(char * username);
			//GET /api/delegates/search?q=username&orderBy=producedblocks:desc
			char * __stdcall SearchDelegate(char * username,char * orderby);
			//GET /api/delegates/count
			char * __stdcall DelegatesCount();
			//GET /api/accounts/delegates/?address=address
			char * __stdcall GetVotesByAddress(char * address);
			//GET /api/delegates/voters?publicKey=publicKey
			char * __stdcall GetVotersByPubkey(char * publicKey);
			//POST /api/delegates/forging/enable
			char * __stdcall EnableForge(char * secret);
			//POST /api/delegates/forging/disable
			char * __stdcall DisableForge(char * secret);
			//GET /api/delegates/forging/getForgedByAccount?generatorPublicKey=generatorPublicKey
			char * __stdcall GetForgedAmount(char * pubkey);
			//GET /api/delegates/getNextForgers?limit=limit
			char * __stdcall GetNextForgers(int limit);
			//-----------------------------------------------finished 2017-1-16----------------------------------------------------
			//PUT /api/dapps
			char * __stdcall RegistDapp(char * secret,char * secondSecret,char * pubkey,char * category,char * name,char * description,char * tags,int type,char * link,char * icon);
			//GET /api/dapps?category=category&name=name&type=type&link=link&limit=limit&offset=offset&orderBy=orderBy
			char * __stdcall GetDapps(char * category,char * name,int type,char * link,int limit,__int32 offset,char * orderBy);
			//GET /api/dapps/get?id=id
			char * __stdcall GetDapp(char * id);
			//GET /api/dapps/search?q=q&category=category&installed=installed
			char * __stdcall SearchDapp(char * query,char * category,int isInstalled);
			//POST /api/dapps/install
			char * __stdcall InstallDapp(char * id);
			//GET /api/dapps/installed
			char * __stdcall InstalledDapps();
			//GET /api/dapps/installedIds
			char * __stdcall InstalledDappIds();
			//POST /api/dapps/uninstall
			char * __stdcall UninstallDapp(char * id);
			//POST /api/dapps/launch
			char * __stdcall LaunchDapp(char * id,char * params);
			//GET /api/dapps/installing
			char * __stdcall InstallingDapps();
			//GET /api/dapps/uninstalling
			char * __stdcall UnInstallingDapps();
			//GET /api/dapps/launched
			char * __stdcall LaunchedDapps();
			//GET /api/dapps/categories
			char * __stdcall Catefories();
			//POST /api/dapps/stop
			char * __stdcall StopDapp(char * id);
			//PUT /api/multisignatures
			char * __stdcall MultiSign(char * secret,int lifetime,int min,char *keysgroup);
			//GET /api/multisignatures/accounts?publicKey=publicKey
			char * __stdcall GetMultiSign(char * publickey);
			//POST /api/multisignatures/sign
			char * __stdcall SignMultiSignature(char * secret,char * publickey,char * txid);
			//GET /api/multisignatures/pending?publicKey=publicKey
			char * __stdcall GetPendingMultiSign(char * publickey);
};
#endif
