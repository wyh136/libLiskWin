// ---------------------------------------------------------------------------
// MADE BY PHINX
#pragma hdrstop

#include "LiskApi.h"
#pragma package(smart_init)
// ---------------------------------------------------------------------------

__stdcall LiskAPI::LiskAPI(char * nodeurl) {
	http = new TIdHTTP();
	AnsiString url=AnsiString(nodeurl);
	if(url.LowerCase().SubString(0,5)=="https")
	{
		ssl=new TIdSSLIOHandlerSocketOpenSSL();
        http->IOHandler=ssl;
	}
	lisknode = nodeurl;
	http->Request->ContentType = "application/json";
}

// ---------------------------------------------------------------------------
__stdcall LiskAPI::LiskAPI() {
	LiskAPI(lisknode);
}

// ---------------------------------------------------------------------------
__stdcall LiskAPI::~LiskAPI() {
	if (!http)
		delete http;
	if(!ssl)
        delete ssl;
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::_request(REQUEST_METHOD request_method, char * url,
	char * data) {
	return HTTPRequest(request_method,(lisknode+url).c_str(),data);
}
char * __stdcall LiskAPI::HTTPRequest(REQUEST_METHOD request_method,char * url,char *data)
{
    TStringStream *ss = NULL;
	if (data != NULL)
		ss = new TStringStream(AnsiString(data), encoding->UTF8, true);
	AnsiString result = "";
	switch (request_method) {
	case RGET:
		result = http->Get(AnsiString(url));
		break;
	case RPOST:
		result = http->Post(AnsiString(url), ss);
		break;
	case RPUT:
		result = http->Put(AnsiString(url), ss);
		break;
	}
	if (ss) {
		ss->Free();
		ss = NULL;
	}
	return result.c_str();
}
// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::_request(char * url /* GET only */) {
	return _request(RGET, url, NULL);
}

// ---------------------------------------------------------------------------   /api/loader/status/ping
char * __stdcall LiskAPI::Ping() {
	return _request("/api/loader/status/ping");
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::Status() {
	return _request("/api/loader/status");
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetAccountBySecret(char * secret) {
	AnsiString data = data.sprintf("{\"secret\": \"%s\"}", secret);
	return _request(RPOST, "/api/accounts/open", data.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::Balance(char * address) //
{
	AnsiString url = url.sprintf("/api/accounts/getBalance?address=%s",
		address);
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::PublicKey(char * address) {
	AnsiString url = url.sprintf("/api/accounts/getPublicKey?address=%s",
		address);
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GenPublicKey(char * secret) //
{
	AnsiString data = data.sprintf("{\"secret\": \"%s\"}", secret);
	return _request(RPOST, "/api/accounts/generatePublicKey", data.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetAccountByAddress(char * address) //
{
	AnsiString url = url.sprintf("/api/accounts?address=%s", address);
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetDelegates(char * address) //
{
	AnsiString url = url.sprintf("/api/accounts/delegates?address=%s", address);
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::DelegatesVote(char * secret, char * second_secret,
	char * pubkey, char *delegates) //
{
	AnsiString data = "";
	AnsiString sec_secret = "";
	if (second_secret != "")
		sec_secret = sec_secret.sprintf("\"secondSecret\":\"%s\",",
		second_secret);
	data = data.sprintf
		("{\"secret\":\"%s\",\"publicKey\":\"%s\",%s \"delegates\":[%s]}",
		secret, pubkey, sec_secret.c_str(), delegates);
	return _request(RPUT, "/api/accounts/delegates", data.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::SyncStatus() {
	return _request("/api/loader/status/sync");
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::Transactions(char * blockID, char * senderId,
	char * recvID, __int64 limit, __int64 offset, char * orderby) {
	AnsiString url = url.sprintf("/api/transactions?blockId=%s", blockID);
	if (limit > 100)
		limit = 100;
	if (senderId != NULL)
		url = url.cat_sprintf("&senderId=%s", senderId);
	if (recvID != NULL)
		url = url.cat_sprintf("&recipientId=%s", recvID);
	if (limit > 0)
		url = url.cat_sprintf("&limit=%d", limit);
	if (offset > 0)
		url = url.cat_sprintf("&offset=%d", offset);
	if (orderby == "")
		orderby = "timestamp:desc";
	url = url.cat_sprintf("&orderBy=%s", orderby);
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::SendTransactions(char * secret, __int64 amount,
	char * recverID, char * publicKey, char * secondSecret) {
	AnsiString data = "", sec_secret = "";

	if (secondSecret != NULL)
		sec_secret = sec_secret.sprintf("\"secondSecret\":\"%s\"",
		secondSecret);
	data = data.sprintf
		("{\"secret\":\"%s\",\"amount\": %d ,\"recipientId\":\"%s\",\"publicKey\":\"%s\",%s}",
		secret, amount, recverID, publicKey, sec_secret.c_str());
	return _request(RPUT, "/api/transactions", data.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetTransactions(char * txid) {
	AnsiString url = url.sprintf("/api/transactions/get?id=%s", txid);
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetUnConfirmedTxByID(char * txid) {
	AnsiString url =
		url.sprintf("/api/transactions/unconfirmed/get?id=%s", txid);
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetUnConfirmedTx() {
	return _request("/api/transactions/unconfirmed");
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetQueuedTx() {
	return _request("/api/transactions/queued");
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetQueuedTxByID(char * txid) {
	AnsiString url = url.sprintf("/api/transactions/queued/get?id=%s", txid);
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetPeers
	(int state /* 1 - disconnected. 2 - connected. 0 - banned */ , char * os,
	char * version, int limit, __int32 offset, char * orderBy) {
	AnsiString url = "/api/peers?";
	if (limit > 100)
		limit = 100;
	if (state != NULL)
		url = url.cat_sprintf("state=%d&", state);
	if (os != NULL)
		url = url.cat_sprintf("os=%s&", os); ;
	if (version != NULL)
		url = url.cat_sprintf("version=%s&", version);
	if (limit > 0)
		url = url.cat_sprintf("limit=%d&", limit);
	if (offset > 0)
		url = url.cat_sprintf("offset=%d&", offset);
	if (orderBy != NULL)
		url = url.cat_sprintf("orderBy=%s&", orderBy);
	else {
		url = url.cat_sprintf("orderBy=%s&", "orderBy=height:desc");
	}
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetPeerByIPEndPoint(char * ip, int port) {
	AnsiString url = url.sprintf("/api/peers/get?ip=%s&port=%d", ip, port);
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::LiskNodeVersion() {
	return _request("/api/peers/version");
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetBlockByID(char * blockid) {
	AnsiString url = url.sprintf("/api/blocks/get?id=%s", blockid);
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetBlocks(__int64 totalfee, __int64 totalAmount,
	char * prevBlock, __int64 height, char * generatorPubKey, int limit,
	__int32 offset, char * orderBy) {
	AnsiString url = "/api/blocks?";
	if (limit > 100)
		limit = 100;
	if (totalfee > 0)
		url = url.cat_sprintf("totalFee=%d&", totalfee);
	if (height > 0)
		url = url.cat_sprintf("height=%d&", height);
	if (totalAmount > 0)
		url = url.cat_sprintf("totalAmount=%d&", totalAmount);
	if (prevBlock != NULL)
		url = url.cat_sprintf("prevBlock=%s&", prevBlock);
	if (generatorPubKey != "")
		url = url.cat_sprintf("generatorPubKey=%s&", generatorPubKey);
	if (limit > 0)
		url = url.cat_sprintf("limit=%d&", limit);
	if (offset > 0)
		url = url.cat_sprintf("offset=%d&", offset);
	if (orderBy != NULL)
		url = url.cat_sprintf("orderBy=%s&", orderBy);
	else {
		url = url.cat_sprintf("orderBy=%d&", "orderBy=timestamp:asc");
	}
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
// GET /api/blocks/getFee
char * __stdcall LiskAPI::GetBlockFee() {
	return _request("/api/blocks/getFee");
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetFees() {
	return _request("/api/blocks/getFees");
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetReward() {
	return _request("/api/blocks/getReward");
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetSupply() {
	return _request("/api/blocks/getSupply");
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetHeight() {
	return _request("/api/blocks/getHeight");
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetStatus() {
	return _request("/api/blocks/getStatus");
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetNethash() {
	return _request("/api/blocks/getNethash");
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetMilestone() {
	return _request("/api/blocks/getMilestone");
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetSignatureFee() {
	return _request("/api/signatures/fee");
}

// ---------------------------------------------------------------------------
// PUT /api/signatures
char * __stdcall LiskAPI::AddSignature(char * secret, char * secondSecret,
	char * publickey) {
	AnsiString data = "";
	AnsiString second_secret = "";
	if (secondSecret != NULL)
		second_secret = second_secret.sprintf("\"secondSecret\":\"%s\"",
		secondSecret);
	data = data.sprintf("{\"secret\":\"%s\",\"publicKey\":\"%s\",%s}", secret,
		publickey, second_secret.c_str());
	return _request(RPUT, "/api/signatures", data.c_str());
}

// ---------------------------------------------------------------------------
// PUT /api/delegates
char * __stdcall LiskAPI::CreateDelegate(char * secret, char * second_secret,
	char * username) {
	AnsiString data = "";
	AnsiString secondSecret = "";
	if (second_secret != NULL)
		secondSecret = secondSecret.sprintf("\"secondSecret\":\"%s\"",
		second_secret);
	data = data.sprintf("{\"secret\":\"%s\",\"username\":\"%s\",%s}", secret,
		username, secondSecret.c_str());
	return _request(RPUT, "/api/delegates", data.c_str());
}

// ---------------------------------------------------------------------------
// GET /api/delegates?limit=limit&offset=offset&orderBy=orderBy
char * __stdcall LiskAPI::DelegatesList(int limit, __int32 offset,
	char * orderBy) {
	AnsiString url = "/api/delegates?";
	if (limit > 100)
		limit = 100;
	if (limit > 0)
		url = url.cat_sprintf("limit=%d&", limit);
	if (offset > 0)
		url = url.cat_sprintf("offset=%d&", offset);
	if (orderBy == NULL)
		url = url.cat_sprintf("orderBy=%s", "timestamp:asc");
	else
		url = url.cat_sprintf("orderBy=%s", orderBy);
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
// GET /api/delegates/get?publicKey=publicKey
char * __stdcall LiskAPI::GetDelegateByPkey(char * publickey) {
	AnsiString url = url.sprintf("/api/delegates/get?publicKey=%s", publickey);
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
char * __stdcall LiskAPI::GetDelegateByName(char * username) {
	AnsiString url = url.sprintf("/api/delegates/get?username=%s", username);
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
// GET /api/delegates/search?q=username&orderBy=producedblocks:desc
char * __stdcall LiskAPI::SearchDelegate(char * username, char * orderBy) {
	AnsiString url = url.sprintf("/api/delegates/search?q=%s&", username);
	if (orderBy == NULL)
		url = url.cat_sprintf("orderBy=%s", "producedblocks:desc");
		else
			url = url.cat_sprintf("orderBy=%s", orderBy);
			 return _request(url.c_str());
}

// ---------------------------------------------------------------------------
// GET /api/delegates/count
char * __stdcall LiskAPI::DelegatesCount() {
	return _request("/api/delegates/count");
}

// ---------------------------------------------------------------------------
// GET /api/accounts/delegates/?address=address
char * __stdcall LiskAPI::GetVotesByAddress(char * address) {
	AnsiString url = url.sprintf("/api/accounts/delegates/?address=%s",
		address);
	return _request(url.c_str());
}

// ---------------------------------------------------------------------------
// GET /api/delegates/voters?publicKey=publicKey
char * __stdcall LiskAPI::GetVotersByPubkey(char * publicKey) {
	AnsiString url = url.sprintf("/api/delegates/voters?publicKey=%s",
		publicKey);
	return _request(url.c_str());
}

// POST /api/delegates/forging/enable
char * __stdcall LiskAPI::EnableForge(char * secret) {
	AnsiString data = data.sprintf("{\"secret\":\"%s\"}", secret);
	return _request(RPOST, "/api/delegates/forging/enable", data.c_str());
}

// POST /api/delegates/forging/disable
char * __stdcall LiskAPI::DisableForge(char * secret) {
	AnsiString data = data.sprintf("{\"secret\":\"%s\"}", secret);
	return _request(RPOST, "/api/delegates/forging/disable", data.c_str());
}

// GET /api/delegates/forging/getForgedByAccount?generatorPublicKey=generatorPublicKey
char * __stdcall LiskAPI::GetForgedAmount(char * pubkey) {
	AnsiString url =
		url.sprintf
		("/api/delegates/forging/getForgedByAccount?generatorPublicKey=%s",
		pubkey);
	return _request(url.c_str());
}

// GET /api/delegates/getNextForgers?limit=limit
char * __stdcall LiskAPI::GetNextForgers(int limit) {
	if (limit > 101)
		limit = 101;
	AnsiString url =
		url.sprintf("/api/delegates/getNextForgers?limit=%d", limit);
	return _request(url.c_str());
}

// -----------------------------------------------------------------------------------------------------
// Dapp functions are not finished. I will be waiting for dapp sdk is released
// PUT /api/dapps
char * __stdcall LiskAPI::RegistDapp(char * secret, char *,
	char * pubkey, char * category, char * name, char * description,
	char * tags, int type, char * link, char * icon) {

}

// -----------------------------------------------------------------------------------------------------
// GET /api/dapps?category=category&name=name&type=type&link=link&limit=limit&offset=offset&orderBy=orderBy
char * __stdcall LiskAPI::GetDapps(char * category, char * name, int type,
	char * link, int limit, __int32 offset, char * orderBy) {

}

// -----------------------------------------------------------------------------------------------------
// GET /api/dapps/get?id=id
char * __stdcall LiskAPI::GetDapp(char * id) {

}

// -----------------------------------------------------------------------------------------------------
// GET /api/dapps/search?q=q&category=category&installed=installed
char * __stdcall LiskAPI::SearchDapp(char * query, char * category,
	int isInstalled) {

}

// -----------------------------------------------------------------------------------------------------
// POST /api/dapps/install
char * __stdcall LiskAPI::InstallDapp(char * id) {

}

// -----------------------------------------------------------------------------------------------------
// GET /api/dapps/installed
char * __stdcall LiskAPI::InstalledDapps() {

}

// -----------------------------------------------------------------------------------------------------
// GET /api/dapps/installedIds
char * __stdcall LiskAPI::InstalledDappIds() {

}

// -----------------------------------------------------------------------------------------------------
// POST /api/dapps/uninstall
char * __stdcall LiskAPI::UninstallDapp(char * id) {

}

// -----------------------------------------------------------------------------------------------------
// POST /api/dapps/launch
char * __stdcall LiskAPI::LaunchDapp(char * id, char * params) {

}

// -----------------------------------------------------------------------------------------------------
// GET /api/dapps/installing
char * __stdcall LiskAPI::InstallingDapps() {

}

// -----------------------------------------------------------------------------------------------------
// GET /api/dapps/uninstalling
char * __stdcall LiskAPI::UnInstallingDapps() {

}

// -----------------------------------------------------------------------------------------------------
// GET /api/dapps/launched
char * __stdcall LiskAPI::LaunchedDapps() {

}

// -----------------------------------------------------------------------------------------------------
// GET /api/dapps/categories
char * __stdcall LiskAPI::Catefories() {

}

// -----------------------------------------------------------------------------------------------------
// POST /api/dapps/stop
char * __stdcall LiskAPI::StopDapp(char * id) {

}

// -----------------------------------------------------------------------------------------------------
// PUT /api/multisignatures
char * __stdcall LiskAPI::MultiSign(char * secret, int lifetime, int min,
	char *keysgroup) {
	AnsiString data = "";
	if (lifetime > 24)
		lifetime = 24;
	if (lifetime < 1)
		lifetime = 1;
	if (min > 15)
		lifetime = 15;
	if (min < 1)
		lifetime = 1;
	data = data.sprintf
		("{\"secret\":\"%s\",\"lifetime\":%d,\"min\":%d,\"keysgroup\":[%s]}",
		secret, lifetime, min, keysgroup);
	return _request(RPUT, "/api/delegates", data.c_str());
}

// -----------------------------------------------------------------------------------------------------
// GET /api/multisignatures/accounts?publicKey=publicKey
char * __stdcall LiskAPI::GetMultiSign(char * publickey) {
	AnsiString url = url.sprintf("/api/multisignatures/accounts?publicKey=%s",
		publickey);
	return _request(url.c_str());
}

// -----------------------------------------------------------------------------------------------------
// POST /api/multisignatures/sign
char * __stdcall LiskAPI::SignMultiSignature(char *  secret,
	char *  publickey, char *  txid) {
	AnsiString data=data.sprintf("{\"secret\":\"%s\",\"publicKey\":\"%s\",\"transactionId\":\"%s\"}",secret,publickey,txid);
	return _request(RPOST, "/api/multisignatures/sign", data.c_str());
}

// -----------------------------------------------------------------------------------------------------
// GET /api/multisignatures/pending?publicKey=publicKey
char * __stdcall LiskAPI::GetPendingMultiSign(char * publickey) {
AnsiString url = url.sprintf("/api/multisignatures/pending?publicKey=%s",
		publickey);
	return _request(url.c_str());
}
