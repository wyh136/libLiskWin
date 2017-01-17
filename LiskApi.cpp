//---------------------------------------------------------------------------
//MADE BY PHINX
#pragma hdrstop

#include "LiskApi.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall LiskAPI::LiskAPI(UnicodeString nodeurl)
{
	http=new TIdHTTP();
    //http->Request->Host=nodeurl;
    lisknode=nodeurl;
	http->Request->ContentType="application/json";
}
//---------------------------------------------------------------------------
__fastcall LiskAPI::LiskAPI()
{
	LiskAPI(lisknode);
}
//---------------------------------------------------------------------------
__fastcall LiskAPI::~LiskAPI()
{
    if(!http)delete http;
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::_request(REQUEST_METHOD request_method,UnicodeString url,TStrings * data)
{
	TStringStream *ss=new TStringStream(data->Text,encoding->UTF8,true);
    UnicodeString result="";
    switch(request_method){
		case RGET:result= http->Get(url);break;
		case RPOST:result=http->Post(url,ss);break;
		case RPUT:result= http->Put(url,ss);break;
	}
	data->Free();
    ss->Free();
    return result;
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::_request(UnicodeString url /*GET only*/)
{
	return _request(RGET,url,new TStringList());
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::Ping()
{

}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::Status()
{
     return _request(lisknode+"/api/loader/status");
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetAccountBySecret(UnicodeString secret)
{
	TStringList *data=new TStringList();
	data->Clear();
	data->Text="{\"secret\": \""+secret+"\"}";
	return _request(RPOST,lisknode+"/api/accounts/open",data);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::Balance(UnicodeString address)  //
{
	return _request(lisknode+"/api/accounts/getBalance?address="+address);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::PublicKey(UnicodeString address)
{
	return _request(lisknode+"/api/accounts/getPublicKey?address="+address);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GenPublicKey(UnicodeString secret)//
{
	TStringList *data=new TStringList();
	data->Clear();
	data->Text="{\"secret\": \""+secret+"\"}";
	return _request(RPOST,lisknode+"/api/accounts/generatePublicKey",data);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetAccountByAddress(UnicodeString address)//
{
	return _request(lisknode+"/api/accounts?address="+address);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetDelegates(UnicodeString address)       //
{
	return _request(lisknode+"/api/accounts/delegates?address="+address);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::DelegatesVote(UnicodeString secret,UnicodeString second_secret,UnicodeString pubkey,TStringList *delegates) //
{
	TStringList *data=new TStringList();
	data->Clear();
	UnicodeString sec_secret="";
	if(second_secret!="")sec_secret="\"secondSecret\":\""+second_secret+"\",";
	data->Text="{\"secret\":\""+secret+"\",\"publicKey\":\""+pubkey+"\","+sec_secret+" \"delegates\":["+delegates->Text+"]}";
	return _request(RPUT,lisknode+"/api/accounts/delegates",data);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::SyncStatus()
{
	return _request(lisknode+"/api/loader/status/sync");
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::Transactions(UnicodeString blockID,UnicodeString senderId,UnicodeString recvID,__int64 limit,__int64 offset,UnicodeString orderby)
{
	UnicodeString limitstr="";
	UnicodeString offsetstr="";
	if(limit>100)limit=100;
	if(orderby=="")orderby="timestamp:desc";
	if(senderId!="")senderId="&senderId="+senderId;
	if(recvID!="")recvID="&recipientId="+recvID;
	if(limit>0)limitstr="&limit="+IntToStr(limit);
	if(offset>0)offsetstr="&offset="+IntToStr(offset);
	return _request(lisknode+"/api/transactions?blockId="+blockID+senderId+recvID+limitstr+offsetstr+"&orderBy="+orderby);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::SendTransactions(UnicodeString secret,__int64 amount,UnicodeString recverID,UnicodeString publicKey,UnicodeString secondSecret)
{
	TStringList *data=new TStringList();
	data->Clear();
	UnicodeString sec_secret="";
	if(secondSecret!="")sec_secret="\"secondSecret\":\""+secondSecret+"\"";
	data->Text="{\"secret\":\""+secret+"\",\"amount\":"+IntToStr(amount)+",\"recipientId\":\""+recverID+"\",\"publicKey\":\""+publicKey+"\","+sec_secret+"}";
	return _request(RPUT,lisknode+"/api/transactions",data);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetTransactions(UnicodeString txid)
{
		return _request(lisknode+"/api/transactions/get?id="+txid);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetUnConfirmedTxByID(UnicodeString txid)
{
	return _request(lisknode+"/api/transactions/unconfirmed/get?id="+txid);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetUnConfirmedTx()
{
	return _request(lisknode+"/api/transactions/unconfirmed");
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetQueuedTx()
{
	return _request(lisknode+"/api/transactions/queued");
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetQueuedTxByID(UnicodeString txid)
{
	return _request(lisknode+"/api/transactions/queued/get?id="+txid);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetPeers(UnicodeString state/*1 - disconnected. 2 - connected. 0 - banned*/,UnicodeString os,UnicodeString version,int limit,__int32 offset,UnicodeString orderBy)
{
	  UnicodeString _state="",_os="",_limit="",_offset="",_orderby="",_version="";
	  if(limit>100)limit=100;
	  if(state!="")_state="state="+state+"&";
	  if(os!="")_os="os="+os+"&";
      if(version!="")_version="version="+version+"&";
	  if(limit>0)_limit="limit="+IntToStr(limit)+"&";
	  if(offset>0)_offset="offset="+IntToStr(offset)+"&";
	  if(orderBy!="")_orderby="orderBy="+orderBy+"&";
	  else{
		 _orderby="orderBy=height:desc" ;
	  }
	  return _request(lisknode+"/api/peers?"+_state+_os+_version+_limit+_offset+_orderby);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetPeerByIPEndPoint(UnicodeString ip,int port)
{
	 return _request(lisknode+"/api/peers/get?ip="+ip+"&port="+IntToStr(port));
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetVersion()
{
	 return _request(lisknode+"/api/peers/version");
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetBlockByID(UnicodeString blockid)
{
	return _request(lisknode+"/api/blocks/get?id="+blockid);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetBlocks(__int64 totalfee,__int64 totalAmount,UnicodeString prevBlock,__int64 height,UnicodeString generatorPubKey,int limit,__int32 offset,UnicodeString orderBy)
{
	  UnicodeString _totalfee="",_totalAmount="",_limit="",_offset="",_orderby="",_prevBlock="",_height="",_generatorPubKey="";
	  if(limit>100)limit=100;
	  if(totalfee>0)_totalfee="totalFee="+IntToStr(totalfee)+"&";
	  if(height>0)_height="height="+IntToStr(height)+"&";
	  if(totalAmount>0)_totalAmount="totalAmount="+IntToStr(totalAmount)+"&";
	  if(prevBlock!="")_prevBlock="prevBlock="+prevBlock+"&";
	  if(generatorPubKey!="")_generatorPubKey="generatorPubKey="+generatorPubKey+"&";
	  if(limit>0)_limit="limit="+IntToStr(limit)+"&";
	  if(offset>0)_offset="offset="+IntToStr(offset)+"&";
	  if(orderBy!="")_orderby="orderBy="+orderBy+"&";
	  else{
		 _orderby="orderBy=timestamp:asc" ;
	  }
	  return _request(lisknode+"/api/blocks?"+_totalfee+_totalAmount+_prevBlock+_generatorPubKey+_height+_limit+_offset+_orderby);
}
//---------------------------------------------------------------------------
			//GET /api/blocks/getFee
UnicodeString __fastcall LiskAPI::GetBlockFee()
{
   return _request(lisknode+"/api/blocks/getFee");
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetFees()
{
   return _request(lisknode+"/api/blocks/getFees");
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetReward()
{
   return _request(lisknode+"/api/blocks/getReward");
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetSupply()
{
	return _request(lisknode+"/api/blocks/getSupply");
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetHeight()
{
	return _request(lisknode+"/api/blocks/getHeight");
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetStatus()
{
	return _request(lisknode+"/api/blocks/getStatus");
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetNethash()
{
	return _request(lisknode+"/api/blocks/getNethash");
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetMilestone()
{
   return _request(lisknode+"/api/blocks/getMilestone");
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetSignatureFee()
{
	return _request(lisknode+"/api/signatures/fee");
}
//---------------------------------------------------------------------------
			//PUT /api/signatures
UnicodeString __fastcall LiskAPI::AddSignature(UnicodeString secret,UnicodeString secondSecret,UnicodeString publickey)
{
	TStringList *data=new TStringList();
	data->Clear();
	UnicodeString second_secret="";
	if(secondSecret!="")second_secret="\"secondSecret\":\""+secondSecret+"\"";
	data->Text="{\"secret\":\""+secret+"\",\"publicKey\":\""+publickey+"\","+second_secret+"}";
	return _request(RPUT,lisknode+"/api/signatures",data);
}
//---------------------------------------------------------------------------
//PUT /api/delegates
UnicodeString __fastcall LiskAPI::CreateDelegate(UnicodeString secret,UnicodeString second_secret,UnicodeString username)
{
	TStringList *data=new TStringList();
	data->Clear();
	UnicodeString secondSecret="";
	if(second_secret!="")secondSecret="\"secondSecret\":\""+second_secret+"\"";
	data->Text="{\"secret\":\""+secret+"\",\"username\":\""+username+"\","+secondSecret+"}";
	return _request(RPUT,lisknode+"/api/delegates",data);
}
//---------------------------------------------------------------------------
			//GET /api/delegates?limit=limit&offset=offset&orderBy=orderBy
UnicodeString __fastcall LiskAPI::DelegatesList(int limit,__int32 offset,UnicodeString orderBy)
{
	 UnicodeString _limit="",_offset="",_orderby="";
	 if(limit>100)limit=100;
	 if(limit>0)_limit="limit="+IntToStr(limit)+"&";
	 if(offset>0)_offset="offset="+IntToStr(offset)+"&";
	 if(orderBy=="")_orderby="orderBy=timestamp:asc";
	 return _request(lisknode+"/api/delegates?"+_limit+_offset+_orderby);
}
//---------------------------------------------------------------------------
			//GET /api/delegates/get?publicKey=publicKey
UnicodeString __fastcall LiskAPI::GetDelegateByPkey(UnicodeString publickey)
{
	return _request(lisknode+"/api/delegates/get?publicKey="+publickey);
}
//---------------------------------------------------------------------------
UnicodeString __fastcall LiskAPI::GetDelegateByName(UnicodeString username)
{
	 return _request(lisknode+"/api/delegates/get?username="+username);
}
//---------------------------------------------------------------------------
//GET /api/delegates/search?q=username&orderBy=producedblocks:desc
UnicodeString __fastcall LiskAPI::SearchDelegate(UnicodeString username,UnicodeString orderBy)
{
    UnicodeString _orderby="";
	if(orderBy=="")_orderby="orderBy=producedblocks:desc";
	return _request(lisknode+"/api/delegates/search?q="+username);
}
//---------------------------------------------------------------------------
//GET /api/delegates/count
UnicodeString __fastcall LiskAPI::DelegatesCount()
{
	return _request(lisknode+"/api/delegates/count");
}
//---------------------------------------------------------------------------
//GET /api/accounts/delegates/?address=address
UnicodeString __fastcall LiskAPI::GetVotesByAddress(UnicodeString address)
{
	return _request(lisknode+"/api/accounts/delegates/?address="+address);
}
//---------------------------------------------------------------------------
//GET /api/delegates/voters?publicKey=publicKey
UnicodeString __fastcall LiskAPI::GetVotersByPubkey(UnicodeString publicKey)
{
   return _request(lisknode+"/api/delegates/voters?publicKey="+publicKey);
}
//POST /api/delegates/forging/enable
UnicodeString __fastcall LiskAPI::EnableForge(UnicodeString secret)
{
   TStringList *data=new TStringList();
   data->Clear();
   data->Text="{\"secret\":\""+secret+"\"}";
   return _request(RPOST,lisknode+"/api/delegates/forging/enable",data);
}
//POST /api/delegates/forging/disable
UnicodeString __fastcall LiskAPI::DisableForge(UnicodeString secret)
{
   TStringList *data=new TStringList();
   data->Clear();
   data->Text="{\"secret\":\""+secret+"\"}";
   return _request(RPOST,lisknode+"/api/delegates/forging/disable",data);
}
			//GET /api/delegates/forging/getForgedByAccount?generatorPublicKey=generatorPublicKey
UnicodeString __fastcall LiskAPI::GetForgedAmount(UnicodeString pubkey)
{
	return _request(lisknode+"/api/delegates/forging/getForgedByAccount?generatorPublicKey="+pubkey);
}
			//GET /api/delegates/getNextForgers?limit=limit
UnicodeString __fastcall LiskAPI::GetNextForgers(int limit)
{
    if(limit>101)limit=101;
	return _request(lisknode+"/api/delegates/getNextForgers?limit="+IntToStr(limit));
}
//-----------------------------------------------------------------------------------------------------
// Dapp functions are not finished. I will be waiting for dapp sdk is released
//PUT /api/dapps
UnicodeString __fastcall LiskAPI::RegistDapp(
UnicodeString secret,UnicodeString secondSecret,UnicodeString pubkey,UnicodeString category,UnicodeString name,UnicodeString description,UnicodeString tags,int type,UnicodeString link,UnicodeString icon)
{
   
}
//-----------------------------------------------------------------------------------------------------
			//GET /api/dapps?category=category&name=name&type=type&link=link&limit=limit&offset=offset&orderBy=orderBy
UnicodeString __fastcall LiskAPI::GetDapps(UnicodeString category,UnicodeString name,int type,UnicodeString link,int limit,__int32 offset,UnicodeString orderBy)
{

}
//-----------------------------------------------------------------------------------------------------
			//GET /api/dapps/get?id=id
UnicodeString __fastcall LiskAPI::GetDapp(UnicodeString id)
{

}
//-----------------------------------------------------------------------------------------------------
			//GET /api/dapps/search?q=q&category=category&installed=installed
UnicodeString __fastcall LiskAPI::SearchDapp(UnicodeString query,UnicodeString category,int isInstalled)
{

}
//-----------------------------------------------------------------------------------------------------
			//POST /api/dapps/install
UnicodeString __fastcall LiskAPI::InstallDapp(UnicodeString id)
{

}
//-----------------------------------------------------------------------------------------------------
			//GET /api/dapps/installed
UnicodeString __fastcall LiskAPI::InstalledDapps()
{

}
//-----------------------------------------------------------------------------------------------------
			//GET /api/dapps/installedIds
UnicodeString __fastcall LiskAPI::InstalledDappIds()
{

}
//-----------------------------------------------------------------------------------------------------
			//POST /api/dapps/uninstall
UnicodeString __fastcall LiskAPI::UninstallDapp(UnicodeString id)
{

}
//-----------------------------------------------------------------------------------------------------
			//POST /api/dapps/launch
UnicodeString __fastcall LiskAPI::LaunchDapp(UnicodeString id,TStringList params)
{

}
//-----------------------------------------------------------------------------------------------------
			//GET /api/dapps/installing
UnicodeString __fastcall LiskAPI::InstallingDapps()
{

}
//-----------------------------------------------------------------------------------------------------
			//GET /api/dapps/uninstalling
UnicodeString __fastcall LiskAPI::UnInstallingDapps()
{

}
//-----------------------------------------------------------------------------------------------------
			//GET /api/dapps/launched
UnicodeString __fastcall LiskAPI::LaunchedDapps()
{

}
//-----------------------------------------------------------------------------------------------------
			//GET /api/dapps/categories
UnicodeString __fastcall LiskAPI::Catefories()
{

}
//-----------------------------------------------------------------------------------------------------
			//POST /api/dapps/stop
UnicodeString __fastcall LiskAPI::StopDapp(UnicodeString id)
{

}
//-----------------------------------------------------------------------------------------------------
			//PUT /api/multisignatures
UnicodeString __fastcall LiskAPI::MultiSign(UnicodeString secret,int lifetime,int min,TStringList *keysgroup)
{
	TStringList *data=new TStringList();
	data->Clear();
	if(lifetime>24)lifetime=24;
	if(lifetime<1)lifetime=1;
	if(min>15)lifetime=15;
	if(min<1)lifetime=1;
	data->Text="{\"secret\":\""+secret+"\",\"lifetime\":\""+IntToStr(lifetime)+"\",\"min\":\""+IntToStr(min)+"\",\"keysgroup\":["+keysgroup->Text+"]}";
	return _request(RPUT,lisknode+"/api/delegates",data);
}
//-----------------------------------------------------------------------------------------------------
			//GET /api/multisignatures/accounts?publicKey=publicKey
UnicodeString __fastcall LiskAPI::GetMultiSign(UnicodeString publickey)
{
	return _request(lisknode+"/api/multisignatures/accounts?publicKey="+publickey);
}
//-----------------------------------------------------------------------------------------------------
			//POST /api/multisignatures/sign
UnicodeString __fastcall LiskAPI::SignMultiSignature(UnicodeString secret,UnicodeString publickey,UnicodeString txid)
{
    TStringList *data=new TStringList();
	data->Clear();
	data->Text="{\"secret\":\""+secret+"\",\"publicKey\":\""+publickey+"\",\"transactionId\":\""+txid+"\"}";
	return _request(RPOST,lisknode+"/api/multisignatures/sign",data);
}
//-----------------------------------------------------------------------------------------------------
			//GET /api/multisignatures/pending?publicKey=publicKey
UnicodeString __fastcall LiskAPI::GetPendingMultiSign(UnicodeString publickey)
{
	 return _request(lisknode+"/api/multisignatures/pending?publicKey="+publickey);
}
