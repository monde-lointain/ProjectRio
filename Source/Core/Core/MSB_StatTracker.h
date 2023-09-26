// Copyright 2023 Project Rio
// SPDX-License-Identifier: GPL-2.0-or-later
// This file is part of Project Rio.

#pragma once

#include <string>
#include <array>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <iostream>
#include "Core/HW/Memmap.h"
#include <picojson.h>

#include "Common/HttpRequest.h"

#include "Common/FileSearch.h"
#include "Common/FileUtil.h"

#include "Core/LocalPlayers.h"
#include "Core/Logger.h"
#include "Core/TrackerAdr.h"

namespace Tag {
class TagSet;
}

enum class GAME_STATE
{
  PREGAME,
  INGAME,
  ENDGAME_LOGGED,
  UNDEFINED
};

static std::map<GAME_STATE, std::string> c_game_state = {
    {GAME_STATE::PREGAME, "PREGAME"},
    {GAME_STATE::INGAME, "INGAME"},
    {GAME_STATE::ENDGAME_LOGGED, "ENDGAME_LOGGED"},
    {GAME_STATE::UNDEFINED, "UNDEFINED"}
};

enum class EVENT_STATE
{
    INIT_EVENT,
    PITCH_RESULT,
    CONTACT_RESULT,
    LOG_FIELDER,
    MONITOR_RUNNERS,
    PLAY_OVER,
    FINAL_RESULT,
    WAITING_FOR_EVENT,
    GAME_OVER,
    UNDEFINED
};

static std::map<EVENT_STATE, std::string> c_event_state = {
    {EVENT_STATE::INIT_EVENT, "INIT_EVENT"},
    {EVENT_STATE::PITCH_RESULT, "PITCH_RESULT"},
    {EVENT_STATE::CONTACT_RESULT, "CONTACT_RESULT"},
    {EVENT_STATE::LOG_FIELDER, "LOG_FIELDER"},
    {EVENT_STATE::MONITOR_RUNNERS, "MONITOR_RUNNERS"},
    {EVENT_STATE::PLAY_OVER, "PLAY_OVER"},
    {EVENT_STATE::FINAL_RESULT, "FINAL_RESULT"},
    {EVENT_STATE::WAITING_FOR_EVENT, "WAITING_FOR_EVENT"},
    {EVENT_STATE::GAME_OVER, "GAME_OVER"},
    {EVENT_STATE::UNDEFINED, "UNDEFINED"}
};



//Conversion Maps

static const std::map<u8, std::string> cCharIdToCharName = {
    {0x0, "Mario"},
    {0x1, "Luigi"},
    {0x2, "DK"},
    {0x3, "Diddy"},
    {0x4, "Peach"},
    {0x5, "Daisy"},
    {0x6, "Yoshi"},
    {0x7, "Baby Mario"},
    {0x8, "Baby Luigi"},
    {0x9, "Bowser"},
    {0xa, "Wario"},
    {0xb, "Waluigi"},
    {0xc, "Koopa(G)"},
    {0xd, "Toad(R)"},
    {0xe, "Boo"},
    {0xf, "Toadette"},
    {0x10, "Shy Guy(R)"},
    {0x11, "Birdo"},
    {0x12, "Monty"},
    {0x13, "Bowser Jr"},
    {0x14, "Paratroopa(R)"},
    {0x15, "Pianta(B)"},
    {0x16, "Pianta(R)"},
    {0x17, "Pianta(Y)"},
    {0x18, "Noki(B)"},
    {0x19, "Noki(R)"},
    {0x1a, "Noki(G)"},
    {0x1b, "Bro(H)"},
    {0x1c, "Toadsworth"},
    {0x1d, "Toad(B)"},
    {0x1e, "Toad(Y)"},
    {0x1f, "Toad(G)"},
    {0x20, "Toad(P)"},
    {0x21, "Magikoopa(B)"},
    {0x22, "Magikoopa(R)"},
    {0x23, "Magikoopa(G)"},
    {0x24, "Magikoopa(Y)"},
    {0x25, "King Boo"},
    {0x26, "Petey"},
    {0x27, "Dixie"},
    {0x28, "Goomba"},
    {0x29, "Paragoomba"},
    {0x2a, "Koopa(R)"},
    {0x2b, "Paratroopa(G)"},
    {0x2c, "Shy Guy(B)"},
    {0x2d, "Shy Guy(Y)"},
    {0x2e, "Shy Guy(G)"},
    {0x2f, "Shy Guy(Bk)"},
    {0x30, "Dry Bones(Gy)"},
    {0x31, "Dry Bones(G)"},
    {0x32, "Dry Bones(R)"},
    {0x33, "Dry Bones(B)"},
    {0x34, "Bro(F)"},
    {0x35, "Bro(B)"}
};

static const std::map<u8, std::string> cStadiumIdToStadiumName = {
    {0x0, "Mario Stadium"},
    {0x1, "Bowser's Castle"},
    {0x2, "Wario's Palace"},
    {0x3, "Yoshi's Island"},
    {0x4, "Peach's Garden"},
    {0x5, "DK's Jungle"},
    {0x6, "Toy Field"}
};

static const std::map<u8, std::string> cTypeOfContactToHR = {
    {0xFF, "Miss"},
    {0, "Sour - Left"},
    {1, "Nice - Left"}, 
    {2, "Perfect"},
    {3, "Nice - Right"}, 
    {4, "Sour - Right"}
};

static const std::map<u8, std::string> cHandToHR = {
    {0, "Right"},
    {1, "Left"}
};

static const std::map<u8, std::string> cInputDirectionToHR = {
    {0, "None"},
    {1, "Towards Batter"},
    {2, "Away From Batter"}
};

static const std::map<u8, std::string> cPitchTypeToHR = {
    {0, "Curve"},
    {1, "Charge"},
    {2, "ChangeUp"}
};

static const std::map<u8, std::string> cChargePitchTypeToHR = {
    {0, "N/A"},
    {2, "Slider"},
    {3, "Perfect"}
};

static const std::map<u8, std::string> cTypeOfSwing = {
    {0, "None"},
    {1, "Slap"},
    {2, "Charge"},
    {3, "Star"},
    {4, "Bunt"}
};

static const std::map<u8, std::string> cPosition = {
    {0, "P"},
    {1, "C"},
    {2, "1B"},
    {3, "2B"},
    {4, "3B"},
    {5, "SS"},
    {6, "LF"},
    {7, "CF"},
    {8, "RF"},
    {0xFF, "Inv"}
};

static const std::map<u8, std::string> cFielderActions = {
    {0, "None"},
    {2, "Sliding"},
    {3, "Walljump"},
};

static const std::map<u8, std::string> cFielderBobbles = {
    {0, "None"},
    {1, "Slide/stun lock"},
    {2, "Fumble"},
    {3, "Bobble"},
    {4, "Fireball"},
    {0x10, "Garlic knockout"},
    {0xFF, "None"}
};

static const std::map<u8, std::string> cStealType = {
    {0, "None"},
    {1, "Ready"},
    {2, "Normal"},
    {3, "Perfect"},
    {0xFF, "None"}
};

static const std::map<u8, std::string> cOutType = {
    {0, "None"},
    {1, "Caught"},
    {2, "Force"},
    {3, "Tag"},
    {4, "Force Back"},
    {0x10, "Strike-out"},
};

static const std::map<u8, std::string> cPitchResult = {
    {0, "HBP"},
    {1, "BB"},
    {2, "Ball"},
    {3, "Strike-looking"},
    {4, "Strike-swing"},
    {5, "Strike-bunting"},
    {6, "Contact"},
    {7, "Unknown"}
};

static const std::map<u8, std::string> cPrimaryContactResult = {
    {0, "Out"},
    {1, "Foul"},
    {2, "Fair"},
    {3, "Fielded"},
    {4, "Unknown"},
};

static const std::map<u8, std::string> cSecondaryContactResult = {
    {0x0,  "Out-caught"},
    {0x1,  "Out-force"},
    {0x2,  "Out-tag"},
    {0x3,  "Foul"},
    {0x4,  "Batter safe, runner out"},
    {0x7,  "Single"},
    {0x8,  "Double"},
    {0x9,  "Triple"},
    {0xA,  "HR"},
    {0xB,  "Error - Input"},
    {0xC,  "Error - Chem"},
    {0xD,  "Bunt"},
    {0xE,  "SacFly"},
    {0xF,  "Ground ball double Play"},
    {0x10, "Foul catch"}
};

static const std::map<u8, std::string> cAtBatResult = {
    {0x0,  "None"},
    {0x1,  "Strikeout"},
    {0x2,  "Walk (BB)"},
    {0x3,  "Walk (HBP)"},
    {0x4,  "Out"},
    {0x5,  "Caught"},
    {0x6,  "Caught line-drive"},
    {0x7,  "Single"},
    {0x8,  "Double"},
    {0x9,  "Triple"},
    {0xA,  "HR"},
    {0xB,  "Error - Input"},
    {0xC,  "Error - Chem"},
    {0xD,  "Bunt"},
    {0xE,  "SacFly"},
    {0xF,  "Ground ball double Play"},
    {0x10, "Foul catch"}
};

static const std::map<u8, std::string> cManualSelectDecode = {
    {0x0,  "No Selected Char"},
    {0x1,  "Pitcher"},
    {0x2,  "Catcher"},
    {0x3,  "Closest to Ball"},
    {0x4,  "Closest to Drop"},
};

//Const for structs
static const int cRosterSize = 9;
static const int cNumOfTeams = 2;
static const int cNumOfPositions = 9;

//Addrs for triggering evts
static const u32 aGameId           = 0x802EBF8C;
static const u32 aEndOfGameFlag    = 0x80892AB3;
static const u32 aWhoQuit          = 0x802EBF93;
static const u32 aGameControlStateCurr = 0x80892aaa;
static const u32 aGameControlStatePrev = 0x80892aab;

static const u32 aAB_PitchThrown     = 0x8088A81B;
static const u32 aAB_ContactResult   = 0x808926B3; //0=InAir, 1=Landed, 2=Landed (almost caught), 3=Caught, FF=Foul
static const u32 aAB_ContactMade     = 0x808909a1; //Boolean, from Roeming
static const u32 aAB_PickoffAttempt  = 0x80892857;

static const u32 aAB_GameIsLive  = 0x8036F3A9; //0 at beginning of game and inbetween innings/changes
static const u32 aAB_PlayIsReadyToStart  = 0x808909AA; //Key addr that tells us when all addrs have been initialized for the play
static const u32 aAB_IsReplay  = 0x80872540;

//Addrs for GameInfo
static const u32 aStadiumId = 0x800E8705;

static const u32 aTeam0_Captain = 0x80353083;
static const u32 aTeam1_Captain = 0x80353087;

static const u32 aTeam0_Captain_Roster_Loc = 0x80892A83;
static const u32 aTeam1_Captain_Roster_Loc = 0x80892A87;

static const u32 aAwayTeam_Score = 0x808928A4;
static const u32 aHomeTeam_Score = 0x808928CA;

static const u32 aInningsSelected = 0x8089294A;

static const u8 c_roster_table_offset = 0xa0;

static const u32 aInGame_CharAttributes_CharId       = 0x80353C05;
static const u32 aInGame_CharAttributes_FieldingHand = 0x80353C06;
static const u32 aInGame_CharAttributes_BattingHand  = 0x80353C07;

//Addrs for DefensiveStats
static const u32 aPitcher_BattersFaced      = 0x803535C9;
static const u32 aPitcher_RunsAllowed       = 0x803535CA;
static const u32 aPitcher_EarnedRuns        = 0x803535CC;
static const u32 aPitcher_BattersWalked     = 0x803535CE;
static const u32 aPitcher_BattersHit        = 0x803535D0;
static const u32 aPitcher_HitsAllowed       = 0x803535D2;
static const u32 aPitcher_HRsAllowed        = 0x803535D4;
static const u32 aPitcher_PitchesThrown     = 0x803535D6;
static const u32 aPitcher_Stamina           = 0x803535D8;
static const u32 aPitcher_WasPitcher        = 0x803535DA;
static const u32 aPitcher_BatterOuts        = 0x803535E1;
static const u32 aPitcher_OutsPitched       = 0x803535E2;
static const u32 aPitcher_StrikeOuts        = 0x803535E4;
static const u32 aPitcher_StarPitchesThrown = 0x803535E5;
static const u32 aPitcher_IsStarred         = 0x8035323B;

static const u8 c_defensive_stat_offset = 0x1E;

//Addrs for OffensiveStats
static const u32 aBatter_AtBats       = 0x803537E8;
static const u32 aBatter_Hits         = 0x803537E9;
static const u32 aBatter_Singles      = 0x803537EA;
static const u32 aBatter_Doubles      = 0x803537EB;
static const u32 aBatter_Triples      = 0x803537EC;
static const u32 aBatter_Homeruns     = 0x803537ED;
static const u32 aBatter_BuntSuccess  = 0x803537EE; //Increments any time a bunt moves a runner
static const u32 aBatter_SacFlys      = 0x803537EF;
static const u32 aBatter_Strikeouts   = 0x803537F1;
static const u32 aBatter_Walks_4Balls = 0x803537F2;
static const u32 aBatter_Walks_Hit    = 0x803537F3;
static const u32 aBatter_RBI          = 0x803537F4;
static const u32 aBatter_BasesStolen  = 0x803537F6;
static const u32 aBatter_BigPlays     = 0x80353807;
static const u32 aBatter_StarHits     = 0x80353808;

static const u8 c_offensive_stat_offset = 0x26;


//Event Scenario 
static const u32 aAB_BatterPort      = 0x802EBF95;
static const u32 aAB_PitcherPort     = 0x802EBF94;
static const u32 aAB_BatterRosterID  = 0x80890971;
static const u32 aAB_Inning          = 0x808928A3;
static const u32 aAB_HalfInning      = 0x8089294D;
static const u32 aAB_Balls           = 0x8089296F;
static const u32 aAB_Strikes         = 0x8089296B;
static const u32 aAB_Outs            = 0x80892973;
static const u32 aAB_P1_Stars        = 0x80892AD6;
static const u32 aAB_P2_Stars        = 0x80892AD7;
static const u32 aAB_IsStarChance    = 0x80892AD8;
static const u32 aAB_ChemLinksOnBase = 0x808909BA;

static const u32 aAB_RunnerOn1       = 0x8088F09D;
static const u32 aAB_RunnerOn2       = 0x8088F1F1;
static const u32 aAB_RunnerOn3       = 0x8088F345;

//Pitch
static const u32 aAB_PitcherRosterID       = 0x80890AD9;
static const u32 aAB_PitcherID             = 0x80890ADB;
static const u32 aAB_PitcherHandedness     = 0x80890B01;
static const u32 aAB_PitchType             = 0x80890B21; //0=Curve, Charge=1, ChangeUp=2
static const u32 aAB_ChargePitchType       = 0x80890B1F; //2=Slider, 3=Perfect
static const u32 aAB_StarPitch_Captain     = 0x80890B25;
static const u32 aAB_StarPitch_NonCaptain  = 0x80890B34;
static const u32 aAB_PitchSpeed            = 0x80890B0A;
static const u32 aAB_PitchCurveInput       = 0x80890A24; //0 if no curve is applied, otherwise its non-zero
static const u32 aAB_PitcherHasCtrlofPitch = 0x80890B12; //Above addr is valid when this addr =1
static const u32 aAB_PitchBallPosZStrikezone  = 0x80890A14;
static const u32 aAB_PitchStrikezoneEdgeLeft  = 0x80890A3C;
static const u32 aAB_PitchStrikezoneEdgeRight = 0x80890A40;

//At-Bat Hit
static const u32 aAB_BallPower      = 0x808926D6;
static const u32 aAB_VertAngle      = 0x808926D2;
static const u32 aAB_HorizAngle      = 0x808926D4;

static const u32 aAB_BallVel_X      = 0x80890E50;
static const u32 aAB_BallVel_Y      = 0x80890E54;
static const u32 aAB_BallVel_Z      = 0x80890E58;

static const u32 aAB_BallAccel_X    = 0x80890E5C;
static const u32 aAB_BallAccel_Y    = 0x80890E60;
static const u32 aAB_BallAccel_Z    = 0x80890E64;

static const u32 aAB_BallContactPos_X = 0x80890934;
static const u32 aAB_BallContactPos_Y = 0x80890938;
static const u32 aAB_BallContactPos_Z = 0x8089093c;

static const u32 aAB_BatContactPos_X = 0x8089095c;
static const u32 aAB_BatContactPos_Y = 0x80890960;
static const u32 aAB_BatContactPos_Z = 0x80890964;

static const u32 aAB_ContactRandInt1 = 0x802ec010;
static const u32 aAB_ContactRandInt2 = 0x802ec012;
static const u32 aAB_ContactRandInt3 = 0x802ec014;

static const u32 aAB_ContactAbsolute = 0x80890950;
static const u32 aAB_ContactQuality  = 0x80890954;
static const u32 aAB_TypeOfSwing    = 0x8089099B; //1=Slap, 2=Charge, 3=Bunt. Set on contact
static const u32 aAB_ChargeUp       = 0x80890968;
static const u32 aAB_ChargeDown     = 0x8089096C;
static const u32 aAB_BatterHand     = 0x8089098B; //Right=0, Left=1
static const u32 aAB_InputDirection = 0x808909B9; //0=None, 1=PullingStickTowardsHitting, 2=PushStickAway
static const u32 aAB_StarSwing      = 0x808909b1; 
static const u32 aAB_MoonShot       = 0x808909B5;
static const u32 aAB_TypeOfContact  = 0x808909A2; //0=Sour, 1=Nice, 2=Perfect, 3=Nice, 4=Sour
static const u32 aAB_RBI            = 0x80893B9A; //RBI for the AB
static const u32 aAB_FramesUnitlBallArrivesBatter  = 0x80890AF2;
static const u32 aAB_TotalFramesOfPitch            = 0x80890AF4;
static const u32 aAB_MissedBall                    = 0x80890b18;

static const u32 aAB_ControlStickInput = 0x8089392C; //P1
static const u8 cControl_Offset = 0x10;

//static const u32 aBattingRandInt1 = 0x802ec010; // short
//static const u32 aBattingRandInt2 = 0x802ec012; // short
//static const u32 aBattingRandInt3 = 0x802ec014; // short

//At-Bat Miss
static const u32 aAB_Miss_SwingOrBunt = 0x808909A9; //(0=NoSwing, 1=Swing, 2=Bunt)
static const u32 aAB_Miss_AnyStrike = 0x80890B17;
static const u32 aAB_AnySwing = 0x8089099D; //1=Charge, Star, or Slap swing

//At-Bat Contact Result
static const u32 aAB_BallPos_X = 0x80890B38;
static const u32 aAB_BallPos_Y = 0x80890B3C;
static const u32 aAB_BallPos_Z = 0x80890B40;

static const u32 aAB_NumOutsDuringPlay = 0x808938AD;
static const u32 aAB_HitByPitch = 0x808909A3;

static const u32 aAB_FinalResult = 0x80893BAA;

//Frame Data. Capture once play is over
static const u32 aAB_FrameOfSwing = 0x80890976; //(halfword) frame of swing animation; stops increasing when contact is made
static const u32 aAB_FrameOfPitchSeqUponSwing    = 0x80890978; //(halfword) frame of pitch that the batter swung

static const u32 aAB_FieldingPort = 0x802EBF94;
static const u32 aAB_BattingPort = 0x802EBF95;

//Fielder addrs
//All of these addrs start with the pitcher. The rest are 0x268 away
static const u32 aFielder_ControlStatus = 0x8088F53B; //0xA=Fielder is holding ball
static const u32 aFielder_CharId = 0x8088F4E3; //Pitcher. Use Filder_Offset to calc the rest 
static const u32 aFielder_RosterLoc = 0x8088F4E1; //Pitcher. Use Filder_Offset to calc the rest 
static const u32 aFielder_AnyJump = 0x8088F56B; //Pitcher
static const u32 aFielder_Action = 0x8088F5C1; //Pitcher. 2=Slide, 3=Walljump
static const u32 aFielder_Bobble = 0x8088F5C0; //Pitcher
static const u32 aFielder_Knockout = 0x8088F578; //Pitcher
static const u32 aFielder_Pos_X = 0x8088F368; //Pitcher
static const u32 aFielder_Pos_Z = 0x8088F370; //Pitcher
static const u32 aFielder_Pos_Y = 0x8088F374; //Pitcher
static const u32 aFielder_ManualSelectArg = 0x802EBF97; //Pitcher
static const u32 cFielder_Offset = 0x268;

//Runner addrs
static const u32 aRunner_BasepathPercentage = 0x8088EE7C;
static const u32 aRunner_RosterLoc = 0x8088EEF9;
static const u32 aRunner_CharId = 0x8088EEFB;
static const u32 aRunner_OutType = 0x8088EF44;
static const u32 aRunner_OutLoc = 0x8088EF3F; //Technically holds the next base
static const u32 aRunner_CurrentBase = 0x8088EF3D;
static const u32 aRunner_Stealing = 0x8088EF66;
static const u32 cRunner_Offset = 0x154;


class StatTracker{
public:
    //StatTracker() { };
    Logger state_logger = Logger("state_log");;

    struct EndGameRosterDefensiveStats{
        u8  batters_faced;
        u16 runs_allowed;
        u16 earned_runs;
        u16 batters_walked;
        u16 batters_hit;
        u16 hits_allowed;
        u16 homeruns_allowed;
        u16 pitches_thrown;
        u16 stamina;
        u8 was_pitcher;
        u8 outs_pitched;
        u8 batter_outs;
        u8 strike_outs;
        u8 star_pitches_thrown;

        u8 big_plays;
    };

    struct EndGameRosterOffensiveStats{
        u32 game_id;
        u32 team_id;
        u32 roster_id;

        u8 at_bats;
        u8 hits;
        u8 singles;
        u8 doubles;
        u8 triples;
        u8 homeruns;
        u8 sac_flys;
        u8 successful_bunts;
        u8 strikouts;
        u8 walks_4balls;
        u8 walks_hit;
        u8 rbi;
        u8 bases_stolen;
        u8 star_hits;
    };

    struct CharacterSummary{
        u8 team_id;
        u8 roster_id;
        u8 char_id;
        u8 is_starred;
        u8 fielding_hand;
        u8 batting_hand;

        EndGameRosterDefensiveStats end_game_defensive_stats;
        EndGameRosterOffensiveStats end_game_offensive_stats;
    };

    struct Runner {
        u8 roster_loc;
        u8 char_id;
        u8 initial_base; //0=Batter, 1=1B, 2=2B, 3=3B
        u8 out_type = 0;
        u8 out_location = 0;
        u8 result_base = 0;
        u8 steal = 0;
        u32 basepath_location = 0;
    };

    struct Fielder {
        u8 fielder_roster_loc;
        u8 fielder_pos;
        u8 fielder_char_id;
        u8 fielder_swapped_for_batter;
        u8 fielder_action = 0; //2=slide, 3=walljump
        u8 fielder_jump = 0; //1=Jump
        u8 fielder_manual_select_arg; //0=No one selected, 1=Other player selected, 2=This player selected
        u32 fielder_x_pos;
        u32 fielder_y_pos;
        u32 fielder_z_pos;
        u8 bobble = 0; //Bobble info
    };

    struct Contact {
        //Vars with 1:1 Adrs
        TrackerAdr<u16> power       = TrackerAdr<u16>("Ball Power", aAB_BallPower, 0xFFFF);
        TrackerAdr<u16> vert_angle  = TrackerAdr<u16>("Vert Angle", aAB_VertAngle, 0xFFFF);
        TrackerAdr<u16> horiz_angle = TrackerAdr<u16>("Horiz Angle", aAB_HorizAngle, 0xFFFF);

        TrackerAdr<u32> ball_x_velo = TrackerAdr<u32>("Ball Velocity - X", aAB_BallVel_X, 0xFFFFFFFF);
        TrackerAdr<u32> ball_y_velo = TrackerAdr<u32>("Ball Velocity - Y", aAB_BallVel_Y, 0xFFFFFFFF);
        TrackerAdr<u32> ball_z_velo = TrackerAdr<u32>("Ball Velocity - Z", aAB_BallVel_Z, 0xFFFFFFFF);

        TrackerAdr<u32> ball_contact_x_pos = TrackerAdr<u32>("Ball Contact Pos - X", aAB_BallContactPos_X, 0xFFFFFFFF);
        TrackerAdr<u32> ball_contact_z_pos = TrackerAdr<u32>("Ball Contact Pos - Z", aAB_BallContactPos_Z, 0xFFFFFFFF);

        TrackerAdr<u32> contact_absolute = TrackerAdr<u32>("Contact Absolute", aAB_ContactAbsolute, 0xFFFFFFFF);
        TrackerAdr<u32> contact_quality = TrackerAdr<u32>("Contact Quality", aAB_ContactQuality, 0xFFFFFFFF);

        TrackerAdr<u16> rng1 = TrackerAdr<u16>("RNG1", aAB_ContactRandInt1, 0xFFFF);
        TrackerAdr<u16> rng2 = TrackerAdr<u16>("RNG2", aAB_ContactRandInt2, 0xFFFF);
        TrackerAdr<u16> rng3 = TrackerAdr<u16>("RNG3", aAB_ContactRandInt3, 0xFFFF);

        //Hit Status
        TrackerAdr<u8> type_of_contact = TrackerAdr<u8>("Type of Contact", aAB_TypeOfContact, 0xFF);
        TrackerAdr<u8> moon_shot = TrackerAdr<u8>("Star Swing Five-Star", aAB_MoonShot, 0xFF);

        //Charge Power
        TrackerAdr<u32> charge_power_up = TrackerAdr<u32>("Charge Power Up", aAB_ChargeUp, 0xFFFFFFFF);
        TrackerAdr<u32> charge_power_down = TrackerAdr<u32>("Charge Power Down", aAB_ChargeDown, 0xFFFFFFFF);
        
        TrackerValue<u8> input_direction_stick = TrackerValue<u8>("Input Direction - Stick", 0);
        TrackerAdr<u8> input_direction_push_pull = TrackerAdr<u8>("Input Direction - Push/Pull", aAB_InputDirection, 0xFF);

        TrackerAdr<u16> frame_of_swing = TrackerAdr<u16>("Frame of Swing Upon Contact", aAB_FrameOfSwing, 0xFFFF);
        
        //Final Result Ball
        TrackerAdr<u32> ball_x_pos = TrackerAdr<u32>("Ball Landing Position - X", aAB_BallPos_X, 0xFFFFFFFF);
        TrackerAdr<u32> ball_y_pos = TrackerAdr<u32>("Ball Landing Position - Y", aAB_BallPos_Y, 0xFFFFFFFF);
        TrackerAdr<u32> ball_z_pos = TrackerAdr<u32>("Ball Landing Position - Z", aAB_BallPos_Z, 0xFFFFFFFF);

        //More ball flight info
        TrackerAdr<u32> ball_max_height = TrackerAdr<u32>("Ball Max Height", 0x8089250c, 0xFFFFFFFF);
        TrackerAdr<u16> ball_hang_time = TrackerAdr<u16>("Ball Hang Time", 0x80892696, 0xFFFF);

        //0=Out
        //1=Foul
        //2=Fair
        //3=Unknown
        u8 primary_contact_result;

        //0=Out-caught
        //1=Out-force
        //2=Out-tag
        //3=foul
        //7=single
        //8=double
        //9=triple
        //A=HR
        //A+=other (sac-fly??, sac-bunt??, GRD??)
        u8 secondary_contact_result;

        std::optional<Fielder> first_fielder;
        std::optional<Fielder> collect_fielder;
    };

    struct Pitch{
        //Pitcher Status
        bool logged = false;
        u8 pitcher_team_id;
        u8 pitcher_char_id;
        u8 pitch_type;
        u8 charge_type;
        u8 star_pitch;
        u8 pitch_speed;

        u8 batter_roster_loc;
        u8 batter_id;

        //Ball pos for pitch visualization
        u32 ball_z_strike_vs_ball;
        u8 ball_in_strikezone;

        TrackerAdr<u32> bat_contact_x_pos = TrackerAdr<u32>("Bat Contact Pos - X", aAB_BatContactPos_X, 0xFFFFFFFF);
        TrackerAdr<u32> bat_contact_z_pos = TrackerAdr<u32>("Bat Contact Pos - Z", aAB_BatContactPos_Z, 0xFFFFFFFF);

        //For integrosity - TODO
        u8 db = 0;
        bool potential_db = false;

        //0=HBP
        //1=BB
        //2=Ball
        //3=Strike-looking
        //4=Strike-swing
        //5=Strike-bunting
        //6=Contact
        //7=Unknown
        u8 pitch_result; 

        //Info about the batter.
        u8 type_of_swing;
        std::optional<Contact> contact;
    };

    struct Event{
        u16 event_num;
        bool pick_off_attempt = false;

        u8 inning;
        u8 half_inning;
        u16 away_score;
        u16 home_score;
        u8 is_star_chance;
        u8 away_stars;
        u8 home_stars;
        u8 chem_links_ob;
        u16 pitcher_stamina;

        u8 pitcher_roster_loc;
        u8 batter_roster_loc;
        u8 catcher_roster_loc;

        u8 balls;
        u8 strikes;
        u8 outs;

        std::optional<Runner> runner_batter;
        std::optional<Runner> runner_1;
        std::optional<Runner> runner_2;
        std::optional<Runner> runner_3;
        std::optional<Pitch>  pitch;

        std::array<u8, cRosterSize> manual_select_locks;

        //Double play or more
        TrackerAdr<u8> num_outs_during_play = TrackerAdr<u8>("Num Outs During Play", aAB_NumOutsDuringPlay, 0xFF);

        u8 rbi;
        u8 result_of_atbat;

        //Partial game. indicates this game has not been finished
        std::pair<bool, bool> write_hud_ab = {true, true};

        std::vector<EVENT_STATE> history;
        std::string stringifyHistory() {
            std::string stringifiedHistory;
            for(EVENT_STATE i : history) {  
                stringifiedHistory += c_event_state[i] + "\n";
            }
            return stringifiedHistory;
        }
    };
    
    struct GameInfo{
        u32 game_id;
        bool init_game = true;
        bool game_active = false;
        std::string start_unix_date_time;
        std::string start_local_date_time;
        std::string end_unix_date_time;
        std::string end_local_date_time;

        u8 team0_port = 0xFF;
        u8 team1_port = 0xFF;
        u8 away_port;
        u8 home_port;

        u8 team0_captain_roster_loc = 0xFF;
        u8 team1_captain_roster_loc = 0xFF;

        LocalPlayers::LocalPlayers::Player team0_player;
        LocalPlayers::LocalPlayers::Player team1_player;
        int avg_ping = 0;
        int lag_spikes = 0;

        //Auto capture
        u16 away_score;
        u16 home_score;

        u8 stadium;

        u8 innings_selected;
        u8 innings_played;

        //Netplay info
        bool netplay;
        std::string netplay_opponent_alias;

        //TagSet info
        std::optional<int> tag_set_id = std::nullopt;

        //Quit?
        u8 quitter_team = 0xFF;

        //Bookkeeping
        //int pitch_num = 0;
        int event_num = 0;

        //Update server with new AB
        bool update_ongoing_game = true;
        bool post_ongoing_game = true;

        //Array of both teams' character summaries
        std::array<std::array<CharacterSummary, cRosterSize>, cNumOfTeams> character_summaries;

        //All of the events for this game
        std::map<u16, Event> events;
        std::optional<Event> previous_state;
        bool write_hud = true;

        //Buffer used to delay the event init by num of frames (60 for now)
        u8 event_init_frame_buffer = 0;
        u8 cNumOfFramesBeforeEventInit = 20;

        std::map<int, LocalPlayers::LocalPlayers::Player> NetplayerUserInfo;  // int is port

        Event& getCurrentEvent() { return events.at(event_num); }
        bool currentEventVld() { return (events.count(event_num) >= 1); }

        LocalPlayers::LocalPlayers::Player getAwayTeamPlayer() { 
            if (team0_port == away_port) {
                return team0_player;
            }
            else{
                return team1_player;
            }
        }
        LocalPlayers::LocalPlayers::Player getHomeTeamPlayer() { 
            if (team0_port == home_port) {
                return team0_player;
            }
            else{
                return team1_player;
            }
        }
    };
    GameInfo m_game_info;

    struct FielderInfo{
        u8 current_pos = 0xFF;
        u8 previous_pos = 0xFF;

        std::array<int, cNumOfPositions> pitch_count_by_position = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::array<int, cNumOfPositions> batter_count_by_position = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::array<int, cNumOfPositions> out_count_by_position   = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::array<int, cNumOfPositions> batter_outs_by_position   = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    };

    struct FielderTracker {

        u8 team_id = 0xFF;
        //Roster_loc, Fielder Info
        //Set changed=true any time the sampled position (each pitch) does not match the current position
        //Rest changed upon new batter
        std::map<u8, FielderInfo> fielder_map = {
            {0, FielderInfo()},
            {1, FielderInfo()},
            {2, FielderInfo()},
            {3, FielderInfo()},
            {4, FielderInfo()},
            {5, FielderInfo()},
            {6, FielderInfo()},
            {7, FielderInfo()},
            {8, FielderInfo()}
        };

        bool initialized = false;
        u8 prev_batter_roster_loc = 0xFF; //Used to check each pitch if the batter has changed.
                                          //Mark current positions when changed

        void initTracker(const Core::CPUThreadGuard& guard, u8 inTeamId){
            team_id = inTeamId;
            initialized = true;
            for (u8 pos=0; pos < cRosterSize; ++pos){
                u32 aFielderRosterLoc_calc = aFielder_RosterLoc + (pos * cFielder_Offset);

                u8 roster_loc = PowerPC::MMU::HostRead_U8(guard, aFielderRosterLoc_calc);

                std::cout << "RosterLoc:" << std::to_string(roster_loc) 
                          << " Init Pos=" << cPosition.at(pos) << std::endl;

                fielder_map[roster_loc].current_pos = pos;
                fielder_map[roster_loc].previous_pos = pos;
            }
        }

        void newBatter() {
            for (auto& kv : fielder_map){
                kv.second.previous_pos = kv.second.current_pos;
            }
        }
        
        //Scans field to see who is playing which position and increments counts for positions
        void evaluateFielders(const Core::CPUThreadGuard& guard) {
            for (u8 pos=0; pos < cRosterSize; ++pos){
                u32 aFielderRosterLoc_calc = aFielder_RosterLoc + (pos * cFielder_Offset);

                u8 roster_loc = PowerPC::MMU::HostRead_U8(guard, aFielderRosterLoc_calc);

                //If new position, mark changed (unless this is the first pitch of the AB (pos==0xFF))
                //Then set new position
                if (fielder_map[roster_loc].current_pos != pos){
                    std::cout << " Team=" << std::to_string(team_id) << " RosterLoc:" << std::to_string(roster_loc) 
                                << " swapped from " << cPosition.at(fielder_map[roster_loc].current_pos)
                                << " to " << cPosition.at(pos) << std::endl; 
                    fielder_map[roster_loc].current_pos = pos; 
                }

                //Increment the number of pitches this player has seen at this position
                ++fielder_map[roster_loc].pitch_count_by_position[pos];
                //std::cout << " Team=" << std::to_string(team_id) << " RosterLoc=" << std::to_string(roster_loc)
                //          << " Pos=" << std::to_string(pos) << "++" << std::endl; 
            }
            return;
        }

        bool outsAtAnyPosition(u8 roster_loc, int starting_pos) {
            for (int pos=starting_pos; pos < cRosterSize; ++pos){
                if (fielder_map[roster_loc].out_count_by_position[pos] > 0) { 
                    return true;
                }
            }
            return false;
        }

        bool pitchesAtAnyPosition(u8 roster_loc, int starting_pos) {
            for (int pos=starting_pos; pos < cRosterSize; ++pos){
                if (fielder_map[roster_loc].pitch_count_by_position[pos] > 0) { 
                    return true;
                }
            }
            return false;
        }

        bool batterOutsAtAnyPosition(u8 roster_loc, int starting_pos) {
            for (int pos=starting_pos; pos < cRosterSize; ++pos){
                if (fielder_map[roster_loc].batter_outs_by_position[pos] > 0) { 
                    return true;
                }
            }
            return false;
        }

        bool battersAtAnyPosition(u8 roster_loc, int starting_pos) {
            for (int pos=starting_pos; pos < cRosterSize; ++pos){
                if (fielder_map[roster_loc].batter_count_by_position[pos] > 0) { 
                    return true;
                }
            }
            return false;
        }

        void incrementOutForPosition(u8 roster_loc, u8 pos){
            ++fielder_map[roster_loc].out_count_by_position[pos];
            //std::cout << " incrementOutForPosition: " << std::to_string(fielder_map[roster_loc].out_count_by_position[pos]);
        }

        void incrementBatterOutForPosition(int num_outs){
            for (u8 roster=0; roster < cRosterSize; ++roster){
                //Increment the number of batter outs this player has seen at this position
                fielder_map[roster].batter_outs_by_position[fielder_map[roster].current_pos] = fielder_map[roster].batter_outs_by_position[fielder_map[roster].current_pos] + num_outs;
                // std::cout << " incrementBatterOutForPosition: " << std::to_string(fielder_map[roster].batter_outs_by_position[fielder_map[roster].current_pos]);
            }
            return;
        }

        void incrementBattersForPosition(){
            for (u8 roster=0; roster < cRosterSize; ++roster){
                //Increment the number of batter outs this player has seen at this position
                ++fielder_map[roster].batter_count_by_position[fielder_map[roster].current_pos];
                // std::cout << " incrementBattersForPosition: " << std::to_string(fielder_map[roster].batter_count_by_position[fielder_map[roster].current_pos]);
            }
            return;
        }

        u8 wasFielderSwappedForBatter(u8 roster_loc){
            if (fielder_map[roster_loc].current_pos != fielder_map[roster_loc].previous_pos){
                return 1;
            }
            return 0;
        }
    };
    std::array<FielderTracker, cNumOfTeams> m_fielder_tracker; //One per team

    void init(){
        //Reset all game info
        m_game_info = GameInfo();
        m_fielder_tracker[0] = FielderTracker();
        m_fielder_tracker[1] = FielderTracker();

        //Reset state machines
        m_game_state  = GAME_STATE::PREGAME;
        m_event_state = EVENT_STATE::INIT_EVENT;
    }

    GAME_STATE  m_game_state  = GAME_STATE::PREGAME;
    GAME_STATE  m_game_state_prev = GAME_STATE::UNDEFINED;
    EVENT_STATE m_event_state = EVENT_STATE::INIT_EVENT;
    EVENT_STATE m_event_state_prev = EVENT_STATE::UNDEFINED;

    struct state_members{
        bool m_netplay_session = false;
        std::optional<int> m_tag_set;
        std::string m_netplay_opponent_alias = "";
        std::optional<int> tag_set_id_local = std::nullopt;
        std::optional<int> tag_set_id_netplay = std::nullopt;
    } m_state;

    union
    {
        u32 num;
        float fnum;
    } float_converter;

    void setTagSetId(Tag::TagSet tag_set, bool netplay);
    void clearTagSetId(bool netplay);
    void setNetplaySession(bool netplay_session, std::string opponent_name = "");
    void setAvgPing(int avgPing);
    void setLagSpikes(int nLagSpikes);
    void setNetplayerUserInfo(std::map<int, LocalPlayers::LocalPlayers::Player> userInfo);
    void setGameID(u32 gameID);
    // void setTags(std::vector tags);
    // void setTagSet(int tagset);

    void Run(const Core::CPUThreadGuard& guard);
    void lookForTriggerEvents(const Core::CPUThreadGuard& guard);

    void logGameInfo(const Core::CPUThreadGuard& guard);
    void logDefensiveStats(const Core::CPUThreadGuard& guard, int team_id, int roster_id);
    void logOffensiveStats(const Core::CPUThreadGuard& guard, int team_id, int roster_id);
    
    void logEventState(const Core::CPUThreadGuard& guard, Event& in_event);
    void logContact(const Core::CPUThreadGuard& guard, Event& in_event);
    void logPitch(const Core::CPUThreadGuard& guard, Event& in_event);
    void logContactResult(const Core::CPUThreadGuard& guard, Contact* in_contact);
    void logFinalResults(const Core::CPUThreadGuard& guard, Event& in_event);
    //void logManualSelectLocks(Event& in_event);

    //Quit function
    void onGameQuit(const Core::CPUThreadGuard& guard);
    bool shouldSubmitGame();

    //RunnerInfo
    std::optional<Runner> logRunnerInfo(const Core::CPUThreadGuard& guard, u8 base);
    bool anyRunnerStealing(const Core::CPUThreadGuard& guard, Event& in_event);
    void logRunnerEvents(const Core::CPUThreadGuard& guard, Runner* in_runner);

    //TODO Redo these tuple functions
    std::optional<Fielder> logFielderWithBall(const Core::CPUThreadGuard& guard);

    std::optional<Fielder> logFielderBobble(const Core::CPUThreadGuard& guard);
    //Read players from ini file and assign to team
    void readPlayerNames(bool local_game);
    //void setDefaultNames(bool local_game);

    float floatConverter(u32 in_value) {
        float out_float;
        float_converter.num = in_value;
        out_float = float_converter.fnum;
        return out_float;
    }

    Common::HttpRequest m_http{std::chrono::minutes{3}};

    //The type of value to decode, the value to be decoded, bool for decode if true or original value if false
    std::string decode(std::string type, u8 value, bool decode);

    //Returns JSON, PathToWriteTo
    std::string getStatJSON(bool inDecode, bool hide_riokey = true);
    std::string getEventJSON(u16 in_event_num, Event& in_event, bool inDecode);
    std::string getHUDJSON(std::string in_event_num, Event& in_curr_event, std::optional<Event> in_prev_event, bool inDecode);
    //Returns path to save json
    std::string getStatJsonPath(std::string prefix);

    void postOngoingGame(Event& in_event);
    void updateOngoingGame(Event& in_event);

    std::pair<u8,u8> getBatterFielderPorts(const Core::CPUThreadGuard& guard){
        // These values are the actual port numbers
        // and are indexed into using the below u8s
        std::array<u8, 2> ports = {PowerPC::MMU::HostRead_U8(guard, 0x800e874c), PowerPC::MMU::HostRead_U8(guard, 0x800e874d)};

        // These registers will always be 0 or 1
        // and swap values each half inning
        u32 BattingTeam = PowerPC::MMU::HostRead_U32(guard, 0x80892990);
        u32 PitchingTeam = PowerPC::MMU::HostRead_U32(guard, 0x80892994);
        
        u8 BattingPort = ports[BattingTeam];
        u8 FieldingPort = ports[PitchingTeam];

        return std::make_pair(BattingPort, FieldingPort);
    }

    /*
    std::pair<u8,u8> getHomeAwayPort(){
        // These values are the actual port numbers
        // and are indexed into using the below u8s
        std::array<u8, 2> ports = {PowerPC::MMU::HostRead_U8(0x800e874c), PowerPC::MMU::HostRead_U8(0x800e874d)};
        
        m_game_info.home_port = ports[0];
        m_game_info.away_port = ports[1];

        return std::make_pair(m_game_info.home_port, m_game_info.away_port);
    }
    */

    void initPlayerInfo(const Core::CPUThreadGuard& guard);
    void initCaptains(const Core::CPUThreadGuard& guard);

    //If mid-game, dump game
    void dumpGame(const Core::CPUThreadGuard& guard){
        if (m_game_state == GAME_STATE::INGAME){
            m_game_info.quitter_team = 2;
            logGameInfo(guard);

            //Remove current event, wasn't finished
            auto it = m_game_info.events.find(m_game_info.event_num);
            if ((&it != NULL) && (it != m_game_info.events.end()))
            {
              m_game_info.events.erase(it);
            }

            //Game has ended. Write file but do not submit
            std::string jsonPath = getStatJsonPath("crash.decode.");
            std::string json = getStatJSON(true);
            
            File::WriteStringToFile(jsonPath, json);

            jsonPath = getStatJsonPath("crash.");
            json = getStatJSON(false, true);
            
            File::WriteStringToFile(jsonPath, json);
            init();
        }
    }
};
