// Database Access by DAO
// Copyright Software Design & Engineering, Robert R. Van Tuyl, 2013.  All rights reserved.


#pragma once
#include "Expandable.h"


#import <C:\Program Files (x86)\Microsoft Office\root\Office16\ACEDAO.DLL> rename(_T("EOF"), _T("DaoEof"))
using namespace DAO;


// Global Function

String getDbCppType(DataTypeEnum type);     // Translate Access Database type value into a c++ type


// Normalizing type definitions from ACEDAO.DLL

typedef _DBEnginePtr EngineP;
typedef Workspace*   WorkspaceP;
typedef DatabasePtr  DatabaseP;
typedef TableDefsPtr TableDefsP;
typedef _TableDefPtr TableDefP;
typedef RecordsetPtr RecordSetP;
typedef FieldsPtr    FieldsP;
typedef _FieldPtr    FieldP;
typedef _com_error   ComError;


enum DaoOptions {DaoDenyWrite      = DAO::dbDenyWrite,
                 DaoDenyRead       = DAO::dbDenyRead,
                 DaoReadOnly       = DAO::dbReadOnly,
                 DaoAppendOnly     = DAO::dbAppendOnly,
                 DaoInconsistent   = DAO::dbInconsistent,
                 DaoConsistent     = DAO::dbConsistent,
                 DaoSQLPassThrough = DAO::dbSQLPassThrough,
                 DaoFailOnError    = DAO::dbFailOnError,
                 DaoForwardOnly    = DAO::dbForwardOnly,
                 DaoSeeChanges     = DAO::dbSeeChanges,
                 DaoRunAsync       = DAO::dbRunAsync,
                 DaoExecDirect     = DAO::dbExecDirect
                 };


class AceDao {
EngineP    engine;
WorkspaceP workspace;
String     path;
DatabaseP  db;

public:

  AceDao();
 ~AceDao();

  bool    open(TCchar* path);             // Database
  void    close();                        // Close Database
  String& getPath() {return path;}


#if 0
  // returns true if database was not opened and was successfully opened.
  // return true if another database was opened and it was closed and the new database was successfully
  // opened.
  // Returns false if database was already opened and it is the same database or not successfully opened.

  bool      opened(TCchar* path);
#endif

  friend class AceTables;
  };


struct TableDesc {
String    name;
TableDefP table;
FieldsP   flds;
int       nFlds;
int       nRcds;

  TableDesc() : table(0), flds(0), nFlds(0), nRcds(0) {}
  TableDesc(TableDesc& dsc) {copy(dsc, *this);}

  TableDesc& operator= (TableDesc& dsc) {copy(dsc, *this); return *this;}

  RecordSetP openRecordSet(DaoOptions option);

private:

  void copy(TableDesc& src, TableDesc& dst);
  };


class AceTables {
AceDao&                  dao;
int                      i;                        // Loop index
bool                     autoOpen;
int                      nTables;
Expandable<TableDesc, 4> tables;

public:

  AceTables(AceDao& acedao);
 ~AceTables() {if (autoOpen) dao.close();}

  int        count() {return nTables;}
  TableDesc* find(TCchar* name);

  TableDesc* startLoop() {i = -1; return nextTable();}
  TableDesc* nextTable() {i++; return i < nTables ? &tables[i] : 0;}
  };


class AceRecordSet {
TableDefP  table;
RecordSetP recordSet;
int        nRecords;

public:

  AceRecordSet() : table(0), recordSet(0), nRecords(0) {}
  AceRecordSet(TableDesc* dsc, DaoOptions option);
  AceRecordSet(const AceRecordSet& rs) : table(rs.table), recordSet(rs.recordSet),
                                                                                 nRecords(rs.nRecords) {}
 ~AceRecordSet() {close();}

  bool       open(TableDesc* dsc, DaoOptions option);
  bool       isOpen() {return recordSet != 0;}
  void       close()  {if (recordSet) recordSet->Close(); recordSet = 0;}

  bool       startLoop();
  bool       nextRecord();

  bool       addNew() {return recordSet ? recordSet->AddNew() == S_OK : false;}
  long       edit()   {return recordSet ? recordSet->Edit()   : 0;}
  long       update();

  RecordSetP getCurRcd() {return recordSet;}

  bool       findRecord(const long    id);
  bool       findRecord(const float   id);
  bool       findRecord(const String& id);

  bool       deleteRecord(const long    rcdID);
  bool       deleteRecord(const float   rcdID);
  bool       deleteRecord(const String& rcdID);
  bool       deleteCurrentRecord();

  AceRecordSet& operator= (const AceRecordSet& rs)
                                    {table = rs.table; recordSet = rs.recordSet; nRecords = rs.nRecords;}
private:

  bstr_t     findPIndex();
  void       openRecordFlds(int rcdType, int rcdOption);
  };


struct AceFldNameDsc {
String       name;
DataTypeEnum type;
long         attr;

  AceFldNameDsc() : type((DataTypeEnum) 0), attr(0) {}
  };


// The field names are stored in the table definition

class AceFieldNames {
TableDefP table;
FieldsP   fields;

int       i;                                // Loop index
int       n;                                // Number of Fields

public:

  AceFieldNames() : table(0), fields(0) , i(0), n(0) {}
  AceFieldNames(TableDesc* dsc) : table(0), fields(0), i(0), n(0)
      {if (!dsc) return; table = dsc->table; fields = table->GetFields(); if (fields) n = fields->Count;}

  bool open(TableDesc* dsc);

  bool isOpen() {return fields != 0;}

  bool startLoop(AceFldNameDsc& fldDsc);
  bool nextDesc( AceFldNameDsc& fldDsc);

  int  noFields() {return n;}
  };


class AceFieldDsc {
FieldP    field;

public:

variant_t value;
long      attr;

  AceFieldDsc() : field(0), value(0), attr(0) {}

  void write(variant_t v);

  friend class AceFields;
  };


// Manage Fields in Current Record

class AceFields {
RecordSetP curRcd;
FieldsP    fields;
FieldP     field;

int        i;                     // Loop variable
int        n;                     // Number of fields in record, used in loop logic

public:

  AceFields(AceRecordSet& currentRcd) : curRcd(currentRcd.getCurRcd()), fields(0), field(0), i(0), n(0)
                               {if (curRcd) fields = curRcd->GetFields(); if (fields) n = fields->Count;}
  bool startLoop(AceFieldDsc& dsc);
  bool nextField(AceFieldDsc& dsc);

  int  noFields() {return n;}
  };



