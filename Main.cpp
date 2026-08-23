#include <plugin.h> // Plugin-SDK version 1002 from 2025-12-09 23:18:09

#include <CAnimManager.h>
#include <CFileLoader.h>

#include "AnimAssocDescriptions.h"
#include "AnimAssocDefinitions.h"

#include <map>

#ifdef DEBUG
#include "CFont.h"
#include "CWeaponInfo.h"
#endif

using namespace plugin;

std::map<std::string, AnimDescriptor*> AnimDescriptorNames = 
{
    { "WALKCYCLE",          aStdAnimDescs },
    { "QUAD",               aQuadDescs },
    { "BIKE",               aBikesDescs },
    { "BIKESTD",            aStdBikeAnimDescs},
    { "IDLE",               aPlayerIdleAnimDescs },
    { "DOOR",               aDoorDescs },
    { "WEAP",               aWeaponDescs },
    { "WEAP1",              aWeaponDescs1 },
    { "WEAP2",              aWeaponDescs2 },
    { "THROW",              aWeaponDescs3 },
    { "MELEE",              aWeaponDescs4 },
    { "MELEE1",             aWeaponDescs5 },
    { "CAR",                aCarAnimDescs1 },
    { "CAR1",               aLowCarAnimDiscs },
    { "CAR2",               aCarAnimDescs2 },
    { "TRUCK",              aTruckAnimDescs },
    { "DRIVEBY",            aDbzAnimDescs },
    { "MEDIC",              aMedicAnimDescs },
    { "BEACH",              aBeachAnimDescs },
    { "SUNBATHE",           aSunbatheAnimDescs },
    { "RIOT",               aRiotAnimDescs },
    { "STRIP",              aStripAnimDescs },
    { "GANGS",              aGangsAnimDescs },
    { "ATTRACTOR",          aAttractorsAnimDescs },
    { "SWIM",               aSwimAnimDescs },
    { "FAT_TIRED",          aFatTiredAnimDescs },
    { "HANDSIGNAL",         aHandSignalAnimDescs },
    { "HANDSIGNAL_LEFT",    aHandSignalLAnimDescs },
    { "HAND",               aHandAnimDescs },
    { "CARRY",              aCarryDescs },
    { "HOUSE",              aIntHouseAnimDescs },
    { "OFFICE",             aIntOfficeAnimDescs },
    { "SHOP",               aIntShopAnimDescs },
    { "STEALTH",            aStealthDescs },
};

tAnimAimOffsets New_ms_aWeaponAimOffsets[NUM_ANIM_ASSOC_GROUPS];

struct Main
{
    Main()
    {
        // pointers
        
        // CAnimationStyleDescriptor* __cdecl CAnimManager::GetAnimGroupName(int index)
        patch::SetPointer(0x4D3A2A + 1, New_ms_aAnimAssocDefinitions);

        // CAnimationStyleDescriptor *__cdecl CAnimManager::AddAnimAssocDefinition(const char *, const char *, int, unsigned int, void *)
        patch::SetPointer(0x4D3BAB + 2, New_ms_aAnimAssocDefinitions);
        patch::SetPointer(0x4D3BB3 + 2, New_ms_aAnimAssocDefinitions);
        patch::SetPointer(0x4D3BDB + 2, New_ms_aAnimAssocDefinitions);
        patch::SetPointer(0x4D3C70 + 2, New_ms_aAnimAssocDefinitions);

        // int __cdecl CAnimManager::CreateAnimAssocGroups()
        patch::SetPointer(0x4D3CDA + 1, &New_ms_aAnimAssocDefinitions->NumAnims);

        // char *__cdecl CAnimManager::GetAnimBlockName(int index)
        patch::SetPointer(0x4D3A3A + 1, New_ms_aAnimAssocDefinitions->BlockName);

        // signed int __cdecl CAnimManager::GetFirstAssocGroup(char *baseName)
        patch::SetPointer(0x4D39B9 + 1, New_ms_aAnimAssocDefinitions->BlockName);

        // gAimingOffset

        // CWeaponInfo::LoadWeaponData
        patch::SetPointer(0x5BED2E + 2, &New_ms_aWeaponAimOffsets->fAimFromX);
        patch::SetPointer(0x5BED38 + 2, &New_ms_aWeaponAimOffsets->fAimFromZ);
        patch::SetPointer(0x5BED42 + 2, &New_ms_aWeaponAimOffsets->fDuckAimX);
        patch::SetPointer(0x5BED4D + 2, &New_ms_aWeaponAimOffsets->fDuckAimZ);
        patch::SetPointer(0x5BED58 + 3, &New_ms_aWeaponAimOffsets->nReloadSampleA);
        patch::SetPointer(0x5BED64 + 3, &New_ms_aWeaponAimOffsets->nReloadSampleB);
        patch::SetPointer(0x5BED70 + 3, &New_ms_aWeaponAimOffsets->nReloadSampleCrouchedA);
        patch::SetPointer(0x5BED77 + 3, &New_ms_aWeaponAimOffsets->nReloadSampleCrouchedB);

        // CWeaponInfo::Initialise
        patch::SetPointer(0x5BF801 + 1, &New_ms_aWeaponAimOffsets->fAimFromZ);

        // CPedIK::PointGunAtPosition
        patch::SetPointer(0x5FDE89 + 2, &New_ms_aWeaponAimOffsets->fDuckAimX);
        patch::SetPointer(0x5FDE91 + 2, &New_ms_aWeaponAimOffsets->fAimFromX);
        patch::SetPointer(0x5FDEC9 + 2, &New_ms_aWeaponAimOffsets->fDuckAimZ);
        patch::SetPointer(0x5FDED1 + 2, &New_ms_aWeaponAimOffsets->fAimFromZ);

        // sub_73A280
        patch::SetPointer(0x4039E1 + 4, &New_ms_aWeaponAimOffsets->nReloadSampleCrouchedA); // HOODLUM
        //patch::SetPointer(0x73A28F + 4, &New_ms_aWeaponAimOffsets->nReloadSampleCrouchedA); // COMPACT
        patch::SetPointer(0x73A29D + 4, &New_ms_aWeaponAimOffsets->nReloadSampleA);

        // sub_73A2B0
        patch::SetPointer(0x73A2BF + 4, &New_ms_aWeaponAimOffsets->nReloadSampleCrouchedB);
        patch::SetPointer(0x73A2CD + 4, &New_ms_aWeaponAimOffsets->nReloadSampleB);

        // CWeaponInfo::GetWeaponReloadTime
        patch::SetPointer(0x743DA8 + 3, &New_ms_aWeaponAimOffsets->nReloadSampleA);
        patch::SetPointer(0x743DBB + 3, &New_ms_aWeaponAimOffsets->nReloadSampleCrouchedA);
        patch::SetPointer(0x743DC9 + 3, &New_ms_aWeaponAimOffsets->nReloadSampleB);
        patch::SetPointer(0x743DDA + 3, &New_ms_aWeaponAimOffsets->nReloadSampleCrouchedB);

        patch::SetPointer(0x5BF825 + 1, &New_ms_aWeaponAimOffsets[NUM_ANIM_ASSOC_GROUPS - 1].fAimFromX);

        patch::RedirectCall(0x5BF738, CAnimManager__ReadAnimAssociationDefinitions);
    };

    static void CAnimManager__ReadAnimAssociationDefinitions()
    {

        // call here original function first
        plugin::Call<0x5BC910>();

        static char Filename[64];
        //std::string PluginName = PLUGIN_FILENAME;
        //PluginName.erase(PluginName.length() - 4, 4);
        //sprintf_s(Filename, "%s.dat", PluginName.data());
        sprintf_s(Filename, "AnimGroupsAddon.dat");

        extern AnimDescriptor aStdAnimDescs[];
        bool loadingAnims = false;
        char* pLine;
        int32_t fid;
        char name[32];
        char file[32];
        char type[32];
        int32_t numAnims;
        CAnimationStyleDescriptor* pDef;

        // failsafe stuff
        char GrpName[32];
        int32_t numAnimsCheck;
        bool bAddToGroup = true;

        CFileMgr::SetDir("");
        //fid = CFileMgr::OpenFile("DATA\\ANIMGRP.DAT", "rb");
        fid = CFileMgr::OpenFile(PLUGIN_PATH(Filename), "rb");

        //assert(fid != 0);

        if (fid == 0)
        {
            //plugin::Error("Unable to open '%s'! \nPlease check if the file is in the same folder and has same name as the plugin!", Filename);
            plugin::Error("Unable to open '%s'! \nPlease check if the file is in the same folder as the plugin!", Filename);
            return;
        }

        int32_t j = 0;
        while ((pLine = CFileLoader::LoadLine(fid)))
        {
            if (*pLine == '#' || *pLine == '\0')
                continue;

            if (loadingAnims == false)
            {
                //if (sscanf(pLine, "%s %s %s %d", name, file, type, &numAnims) != 4)
                if (sscanf(pLine, "%s %s %s %d", GrpName, file, type, &numAnims) != 4)
                {
                    //assert(0, "Corrupt animgrp.dat");
                    //plugin::Error("Corrupt AnimGroupsSA.dat");

                    if (GrpName)
                        plugin::Error("Error loading '%s' animation group header! Not enought parameters!", GrpName);
                    else
                        plugin::Error("Error loading animation group header! Not enought parameters!");
                    return;
                }

                //  Original code
                //pDef = CAnimManager::AddAnimAssocDefinition(name, file, MODEL_MALE01, numAnims, aStdAnimDescs);

                //   New code
                AnimDescriptor* AnimDsc = GetDescriptorForAnimGroup(type);

                if (AnimDsc)
                {
                    //pDef = CAnimManager::AddAnimAssocDefinition(name, file, MODEL_MALE01, numAnims, AnimDsc);
                    pDef = CAnimManager::AddAnimAssocDefinition(GrpName, file, MODEL_MALE01, numAnims, AnimDsc);

                    bAddToGroup = true;
                }
                else
                {
                    plugin::Error("Unvalid '%s' animation group descriptor '%s'!", GrpName, type);

                    // don't skip all other groups, but don't load them until we find next END
                    bAddToGroup = false;
                }

                loadingAnims = true;

                //

                // failsafe

                numAnimsCheck = 0;

                //
            }
            else
            {
                if (sscanf(pLine, "%s", name) == 1)
                {
                    if (!strcmp(name, "end"))
                    {
                        loadingAnims = false;

                        if (numAnimsCheck < numAnims)
                        {
                            plugin::Error("The number of animations in the '%s' group is less than specified! \n\nNumber of required animations: %d", GrpName, numAnims);
                        }
                    }
                    else
                    {
                        if (numAnimsCheck >= numAnims)
                        {
                            plugin::Error("'%s' group has more animations than specified! \n\nNumber of required animations: %d", GrpName, numAnims);
                            continue;
                        }

                        if (bAddToGroup)
                            CAnimManager::AddAnimToAssocDefinition(pDef, name);

                        numAnimsCheck++;
                    }
                }
            }
        }

        //assert(loadingAnims == false, "Corrupt animgrp.dat");

        if (loadingAnims == true)
            plugin::Error("Corrupt '%s'! Animation group '%s' doesn't have 'END' directive!", Filename, name);

        CFileMgr::CloseFile(fid);
    }

    static AnimDescriptor* GetDescriptorForAnimGroup(char* DescName)
    {
        std::string CmpStr = DescName;
        CmpStr = ToUpper(CmpStr, 0);

        if (AnimDescriptorNames.contains(CmpStr))
            return AnimDescriptorNames[CmpStr];
        else
            //return aStdAnimDescs;
            return nullptr;
    }
} gInstance;
