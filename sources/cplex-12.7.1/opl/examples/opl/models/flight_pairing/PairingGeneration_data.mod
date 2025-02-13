// --------------------------------------------------------------------------
// Licensed Materials - Property of IBM
//
// 5725-A06 5725-A29 5724-Y48 5724-Y49 5724-Y54 5724-Y55
// Copyright IBM Corporation 1998, 2015. All Rights Reserved.
//
// Note to U.S. Government Users Restricted Rights:
// Use, duplication or disclosure restricted by GSA ADP Schedule
// Contract with IBM Corp.
// --------------------------------------------------------------------------

tuple TPairingGenerationData {
  int   DebugMode;
  int   PrintFiles; // 1: write: 0: dont write
  /// initial pairings
  int   NumberOfInitialPairings;
  ///   below this value, duals are meaningless.
  float DualThreshold;
  /// used when solving slave model to find new column.
  int   SlaveModelBranchLimit;
  /// 
  int   NumberOfRandomColumns;
};

TPairingGenerationData PairingGenerationData = ...;