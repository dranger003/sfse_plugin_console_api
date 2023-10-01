#include "pch.h"

namespace plugin
{
	const std::vector<std::string> utils::form_type_names = {
		"NONE",	// 00
		"TES4",	// 01
		"GRUP",	// 02
		"GMST",	// 03
		"KYWD",	// 04 BGSKeyword
		"FFKW",	// 05 BGSFormFolderKeywordList
		"LCRT",	// 06 BGSLocationRefType
		"AACT",	// 07 BGSAction
		"TRNS",	// 08 BGSTransform
		"TXST",	// 09 BGSTextureSet
		"GLOB",	// 0A TESGlobal
		"DMGT",	// 0B BGSDamageType
		"CLAS",	// 0C TESClass
		"FACT",	// 0D TESFaction
		"AFFE",	// 0E BGSAffinityEvent
		"HDPT",	// 0F BGSHeadPart
		"EYES",	// 10 TESEyes
		"RACE",	// 11 TESRace
		"SOUN",	// 12 TESSound
		"SECH",	// 13 BGSSoundEcho
		"ASPC",	// 14 BGSAcousticSpace
		"AOPF",	// 15 BGSAudioOcclusionPrimitive
		"SKIL",	// 16
		"MGEF",	// 17 EffectSetting
		"SCPT",	// 18 Script
		"LTEX",	// 19 TESLandTexture
		"PDCL",	// 1A BGSProjectedDecal
		"ENCH",	// 1B EnchantmentItem
		"SPEL",	// 1C SpellItem
		"SCRL",	// 1D ScrollItem
		"ACTI",	// 1E TESObjectACTI
		"TACT",	// 1F BGSTalkingActivator
		"CURV",	// 20 BGSCurveForm
		"CUR3",	// 21 BGSCurve3DForm
		"ARMO",	// 22 TESObjectARMO
		"BOOK",	// 23 TESObjectBOOK
		"CONT",	// 24 TESObjectCONT
		"DOOR",	// 25 TESObjectDOOR
		"INGR",	// 26 IngredientItem
		"LIGH",	// 27 TESObjectLIGH
		"MISC",	// 28 TESObjectMISC
		"STAT",	// 29 TESObjectSTAT
		"SCOL",	// 2A BGSStaticCollection
		"PKIN",	// 2B BGSPackIn
		"MSTT",	// 2C BGSMovableStatic
		"GRAS",	// 2D TESGrass
		"FLOR",	// 2E TESFlora
		"FURN",	// 2F TESFurniture
		"WEAP",	// 30 TESObjectWEAP
		"AMMO",	// 31 TESAmmo
		"NPC_",	// 32 TESNPC
		"LVLN",	// 33 TESLevCharacter
		"LVLP",	// 34 BGSLevPackIn
		"KEYM",	// 35 TESKey
		"ALCH",	// 36 AlchemyItem
		"IDLM",	// 37 BGSIdleMarker
		"BMMO",	// 38 BGSBiomeMarkerObject
		"NOTE",	// 39 BGSNote
		"PROJ",	// 3A BGSProjectile
		"HAZD",	// 3B BGSHazard
		"BNDS",	// 3C BGSBendableSpline
		"SLGM",	// 3D TESSoulGem
		"TERM",	// 3E BGSTerminal
		"LVLI",	// 3F TESLevItem
		"GBFT",	// 40 BGSGenericBaseFormTemplate
		"GBFM",	// 41 BGSGenericBaseForm
		"LVLB",	// 42 BGSLevGenericBaseForm
		"WTHR",	// 43 TESWeather
		"WTHS",	// 44 BGSWeatherSettingsForm
		"CLMT",	// 45 TESClimate
		"SPGD",	// 46 BGSShaderParticleGeometryData
		"REGN",	// 47 TESRegion
		"NAVI",	// 48 NavMeshInfoMap
		"CELL",	// 49 TESObjectCELL
		"REFR",	// 4A TESObjectREFR
		"ACHR",	// 4B Actor
		"PMIS",	// 4C MissileProjectile
		"PARW",	// 4D ArrowProjectile
		"PGRE",	// 4E GrenadeProjectile
		"PBEA",	// 4F BeamProjectile
		"PFLA",	// 50 FlameProjectile
		"PCON",	// 51 ConeProjectile
		"PPLA",	// 52 PlasmaProjectile
		"PBAR",	// 53 BarrierProjectile
		"PEMI",	// 54 EmitterProjectile
		"PHZD",	// 55 Hazard
		"WRLD",	// 56 TESWorldSpace
		"NAVM",	// 57 NavMesh
		"TLOD",	// 58
		"DIAL",	// 59 TESTopic
		"INFO",	// 5A TESTopicInfo
		"QUST",	// 5B TESQuest
		"IDLE",	// 5C TESIdleForm
		"PACK",	// 5D TESPackage
		"CSTY",	// 5E TESCombatStyle
		"LSCR",	// 5F TESLoadScreen
		"LVSP",	// 60 TESLevSpell
		"ANIO",	// 61 TESObjectANIO
		"WATR",	// 62 TESWaterForm
		"EFSH",	// 63 TESEffectShader
		"TOFT",	// 64
		"EXPL",	// 65 BGSExplosion
		"DEBR",	// 66 BGSDebris
		"IMGS",	// 67 TESImageSpace
		"IMAD",	// 68 TESImageSpaceModifier
		"FLST",	// 69 BGSListForm
		"PERK",	// 6A BGSPerk
		"BPTD",	// 6B BGSBodyPartData
		"ADDN",	// 6C BGSAddonNode
		"AVIF",	// 6D ActorValueInfo
		"CAMS",	// 6E BGSCameraShot
		"CPTH",	// 6F BGSCameraPath
		"VTYP",	// 70 BGSVoiceType
		"MATT",	// 71 BGSMaterialType
		"IPCT",	// 72 BGSImpactData
		"IPDS",	// 73 BGSImpactDataSet
		"ARMA",	// 74 TESObjectARMA
		"LCTN",	// 75 BGSLocation
		"MESG",	// 76 BGSMessage
		"RGDL",	// 77
		"DOBJ",	// 78 BGSDefaultObjectManager
		"DFOB",	// 79 BGSDefaultObject
		"LGTM",	// 7A BGSLightingTemplate
		"MUSC",	// 7B BGSMusicType
		"FSTP",	// 7C BGSFootstep
		"FSTS",	// 7D BGSFootstepSet
		"SMBN",	// 7E BGSStoryManagerBranchNode
		"SMQN",	// 7F BGSStoryManagerQuestNode
		"SMEN",	// 80 BGSStoryManagerEventNode
		"DLBR",	// 81 BGSDialogueBranch
		"MUST",	// 82 BGSMusicTrackFormWrapper
		"DLVW",	// 83
		"WOOP",	// 84 TESWordOfPower
		"SHOU",	// 85 TESShout
		"EQUP",	// 86 BGSEquipSlot
		"RELA",	// 87 BGSRelationship
		"SCEN",	// 88 BGSScene
		"ASTP",	// 89 BGSAssociationType
		"OTFT",	// 8A BGSOutfit
		"ARTO",	// 8B BGSArtObject
		"MATO",	// 8C BGSMaterialObject
		"MOVT",	// 8D BGSMovementType
		"DUAL",	// 8E BGSDualCastData
		"COLL",	// 8F BGSCollisionLayer
		"CLFM",	// 90 BGSColorForm
		"REVB",	// 91 BGSReverbParameters
		"RFGP",	// 92 BGSReferenceGroup
		"AMDL",	// 93 BGSAimModel
		"AAMD",	// 94 BGSAimAssistModel
		"MAAM",	// 95 BGSMeleeAimAssistModel
		"LAYR",	// 96
		"COBJ",	// 97 BGSConstructibleObject
		"OMOD",	// 98 BGSMod::Attachment::Mod
		"ZOOM",	// 99 BGSAimDownSightModel
		"INNR",	// 9A BGSInstanceNamingRules
		"KSSM",	// 9B BGSSoundKeywordMapping
		"SCCO",	// 9C
		"AORU",	// 9D BGSAttractionRule
		"STAG",	// 9E BGSSoundTagSet
		"IRES",	// 9F BGSResource
		"BIOM",	// A0 BGSBiome
		"NOCM",	// A1 NavMeshObstacleCoverManager
		"LENS",	// A2 BGSLensFlare
		"LSPR",	// A3
		"OVIS",	// A4 BGSObjectVisibilityManager
		"DLYR",	// A5
		"STND",	// A6 BGSSnapTemplateNode
		"STMP",	// A7 BGSSnapTemplate
		"GCVR",	// A8 BGSGroundCover
		"MRPH",	// A9 BGSMorphableObject
		"TRAV",	// AA BGSTraversal
		"RSGD",	// AB BGSResourceGenerationData
		"OSWP",	// AC BGSObjectSwap
		"ATMO",	// AD BGSAtmosphere
		"LVSC",	// AE BGSLevSpaceCell
		"SPCH",	// AF BGSSpeechChallengeObject
		"RESO",	// B0
		"AAPD",	// B1 BGSAimAssistPoseData
		"VOLI",	// B2 BGSVolumetricLighting
		"SFBK",	// B3 BGSSurface::Block
		"SFPC",	// B4
		"SFPT",	// B5 BGSSurface::Pattern
		"SFTR",	// B6 BGSSurface::Tree
		"PCMT",	// B7 BGSPlanetContentManagerTree
		"BMOD",	// B8 BGSBoneModifier
		"STBH",	// B9 BGSSnapBehavior
		"PNDT",	// BA BGSPlanet::PlanetData
		"IUTF",	// BB
		"CNDF",	// BC BGSConditionForm
		"PCBN",	// BD BGSPlanetContentManagerBranchNode
		"PCCN",	// BE BGSPlanetContentManagerContentNode
		"STDT",	// BF BSGalaxy::BGSStar
		"WWED",	// C0 BGSWwiseEventForm
		"RSPJ",	// C1 BGSResearchProjectForm
		"AOPS",	// C2 BGSAimOpticalSightModel
		"AMBS",	// C3 BGSAmbienceSet
		"WBAR",	// C4 BGSWeaponBarrelModel
		"PTST",	// C5 BGSSurface::PatternStyle
		"LMSW",	// C6 BGSLayeredMaterialSwap
		"FORC",	// C7 BGSForceData
		"TMLM",	// C8 BGSTerminalMenu
		"EFSQ",	// C9 BGSEffectSequenceForm
		"SDLT",	// CA BGSSecondaryDamageList
		"MTPT",	// CB BGSMaterialPathForm
		"CLDF",	// CC BGSCloudForm
		"FOGV",	// CD BGSFogVolumeForm
		"WKMF",	// CE BGSWwiseKeywordMapping
		"LGDI",	// CF BGSLegendaryItem
		"PSDC",	// D0 BGSParticleSystemDefineCollection
		"SUNP",	// D1 BSGalaxy::BGSSunPresetForm
		"PMFT",	// D2 BGSPhotoModeFeature
		"TODD",	// D3 BGSTimeOfDayData
		"AVMD",	// D4 BGSAVMData
		"PERS",	// D5 TESDataHandlerPersistentCreatedUtil::BGSPersistentIDsForm
		"CHAL",	// D6 BGSChallengeForm
	};
}
