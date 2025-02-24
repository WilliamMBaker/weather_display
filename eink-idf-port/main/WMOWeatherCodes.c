#include "WMOWeatherCodes.h"

int parse_WMO(int code)
{
	switch (code)
	{
		case WMO_NO_PERCIP_CODE_00: // Cloud development not observed or not observable, Characteristic change of the state of sky during the past hour
		case WMO_NO_PERCIP_CODE_01: // Clouds generally dissolving or becoming less developed, Characteristic change of the state of sky during the past hour
		case WMO_NO_PERCIP_CODE_02: // State of sky on the whole unchanged, Characteristic change of the state of sky during the past hour
		case WMO_NO_PERCIP_CODE_03: // Clouds generally forming or developing, Characteristic change of the state of sky during the past hour
		case WMO_NO_PERCIP_CODE_04: // Visibility reduced by smoke, e.g. veldt or forest fires, industrial smoke or volcanic ashes
		case WMO_NO_PERCIP_CODE_05: // Haze
		case WMO_NO_PERCIP_CODE_06: // Widespread dust in suspension in the air, not raised by wind at or near the station at the time of observation
		case WMO_NO_PERCIP_CODE_07: // Dust or sand raised by wind at or near the station at the time of observation, but no well developed dust whirl(s) or sand whirl(s), and no duststorm or sandstorm seen
		case WMO_NO_PERCIP_CODE_08: // Well developed dust whirl(s) or sand whirl(s) seen at or near the station during the preceding hour or at the time ot observation, but no duststorm or sandstorm
		case WMO_NO_PERCIP_CODE_09: // Duststorm or sandstorm within sight at the time of observation, or at the station during the preceding hour
		case WMO_NO_PERCIP_CODE_10: // Mist
		case WMO_NO_PERCIP_CODE_11: // Patches, shallow fog or ice fog at the station, whether on land or sea, not deeper than about 2 metres on land or 10 metres at sea
		case WMO_NO_PERCIP_CODE_12: // More or less continuous, shallow fog or ice fog at the station, whether on land or sea, not deeper than about 2 metres on land or 10 metres at sea
		case WMO_NO_PERCIP_CODE_13: // Lightning visible, no thunder heard
		case WMO_NO_PERCIP_CODE_14: // Precipitation within sight, not reaching the ground or the surface of the sea
		case WMO_NO_PERCIP_CODE_15: // Precipitation within sight, reaching the ground or the surface of the sea, but distant, i.e. estimated to be more than 5 km from the station
		case WMO_NO_PERCIP_CODE_16: // Precipitation within sight, reaching the ground or the surface of the sea, near to, but not at the station
		case WMO_NO_PERCIP_CODE_17: // Thunderstorm, but no precipitation at the time of observation
		case WMO_NO_PERCIP_CODE_18: // Squalls 	at or within sight of the station during the preceding hour or at the time of observation
		case WMO_NO_PERCIP_CODE_19: // Funnel cloud (Tornado cloud or water-spout)
		case WMO_PERCIP_CODE_20: // Drizzle (not freezing) or snow grains, not falling as shower(s)
		case WMO_PERCIP_CODE_21: // Rain (not freezing), not falling as shower(s)
		case WMO_PERCIP_CODE_22: // Snow, not falling as shower(s)
		case WMO_PERCIP_CODE_23: // Rain and snow or ice pellets, not falling as shower(s)
		case WMO_PERCIP_CODE_24: // Freezing drizzle or freezing rain, not falling as shower(s)
		case WMO_PERCIP_CODE_25: // Shower(s) of rain
		case WMO_PERCIP_CODE_26: // Shower(s) of snow, or of rain and snow
		case WMO_PERCIP_CODE_27: // Shower(s) of hail*, or of rain and hail*
		case WMO_PERCIP_CODE_28: // Fog or ice fog
		case WMO_PERCIP_CODE_29: // Thunderstorm (with or without precipitation)
		case WMO_PART_CODE_30: // Slight or moderate duststorm or sandstorm, has decreased during the preceding hour
		case WMO_PART_CODE_31: // Slight or moderate duststorm or sandstorm, no appreciable change during the preceding hour
		case WMO_PART_CODE_32: // Slight or moderate duststorm or sandstorm, has begun or has increased during the preceding hour
		case WMO_PART_CODE_33: // Severe duststorm or sandstorm, has decreased during the preceding hour
		case WMO_PART_CODE_34: // Severe duststorm or sandstorm, no appreciable change during the preceding hour
		case WMO_PART_CODE_35: // Severe duststorm or sandstorm, has begun or has increased during the preceding hour
		case WMO_PART_CODE_36: // Slight or moderate blowing snow generally low (below eye level)
		case WMO_PART_CODE_37: // Heavy drifting snow generally low (below eye level)
		case WMO_PART_CODE_38: // Slight or moderate blowing snow generally high (above eye level)
		case WMO_PART_CODE_39: // Heavy drifting snow generally high (above eye level)
		case WMO_ICE_FOG_CODE_40: // Fog or ice fog at a distance at the time of observation, but not at the station during the preceding hour, the fog or ice fog extending to a level above that of the observer
		case WMO_ICE_FOG_CODE_41: // Fog or ice fog in patches
		case WMO_ICE_FOG_CODE_42: // Fog or ice fog, sky visible, has become thinner during the preceding hour
		case WMO_ICE_FOG_CODE_43: // Fog or ice fog, sky invisible, has become thinner during the preceding hour
		case WMO_ICE_FOG_CODE_44: // Fog or ice fog, sky visible, no appreciable change during the preceding hour
		case WMO_ICE_FOG_CODE_45: // Fog or ice fog, sky invisible, no appreciable change during the preceding hour
		case WMO_ICE_FOG_CODE_46: // Fog or ice fog, sky visible, has begun or has become thicker during the preceding hour
		case WMO_ICE_FOG_CODE_47: // Fog or ice fog, sky invisible, has begun or has become thicker during the preceding hour
		case WMO_ICE_FOG_CODE_48: // Fog, depositing rime, sky visible
		case WMO_ICE_FOG_CODE_49: // Fog, depositing rime, sky invisible
		case WMO_DRIZZLE_CODE_50: // Drizzle, not freezing, intermittent, slight at time of observation
		case WMO_DRIZZLE_CODE_51: // Drizzle, not freezing, continuous, slight at time of observation
		case WMO_DRIZZLE_CODE_52: // Drizzle, not freezing, intermittent, moderate at time of observation
		case WMO_DRIZZLE_CODE_53: // Drizzle, not freezing, continuous, moderate at time of observation
		case WMO_DRIZZLE_CODE_54: // Drizzle, not freezing, intermittent, heavy (dense) at time of observation
		case WMO_DRIZZLE_CODE_55: // Drizzle, not freezing, continuous, heavy (dense) at time of observation
		case WMO_DRIZZLE_CODE_56: // Drizzle, freezing, slight
		case WMO_DRIZZLE_CODE_57: // Drizzle, freezing, moderate or heavy (dence)
		case WMO_DRIZZLE_CODE_58: // Drizzle and rain, slight
		case WMO_DRIZZLE_CODE_59: // Drizzle and rain, moderate or heavy
		case WMO_RAIN_CODE_60: // Rain, not freezing, intermittent, slight at time of observation
		case WMO_RAIN_CODE_61: // Rain, not freezing, continuous, slight at time of observation
		case WMO_RAIN_CODE_62: // Rain, not freezing, intermittent, moderate at time of observation
		case WMO_RAIN_CODE_63: // Rain, not freezing, continuous, moderate at time of observation
		case WMO_RAIN_CODE_64: // Rain, not freezing, intermittent, heavy at time of observation
		case WMO_RAIN_CODE_65: // Rain, not freezing, continuous, heavy at time of observation
		case WMO_RAIN_CODE_66: // Rain, freezing, slight
		case WMO_RAIN_CODE_67: // Rain, freezing, moderate or heavy (dence)
		case WMO_RAIN_CODE_68: // Rain or drizzle and snow, slight
		case WMO_RAIN_CODE_69: // Rain or drizzle and snow, moderate or heavy
		case WMO_SOLID_PERCIP_CODE_70: // Intermittent fall of snowflakes, slight at time of observation
		case WMO_SOLID_PERCIP_CODE_71: // Continuous fall of snowflakes, slight at time of observation
		case WMO_SOLID_PERCIP_CODE_72: // Intermittent fall of snowflakes, moderate at time of observation
		case WMO_SOLID_PERCIP_CODE_73: // Continuous fall of snowflakes, moderate at time of observation
		case WMO_SOLID_PERCIP_CODE_74: // Intermittent fall of snowflakes, heavy at time of observation
		case WMO_SOLID_PERCIP_CODE_75: // Continuous fall of snowflakes, heavy at time of observation
		case WMO_SOLID_PERCIP_CODE_76: // Diamond dust (with or without fog)
		case WMO_SOLID_PERCIP_CODE_77: // Snow grains (with or without fog)
		case WMO_SOLID_PERCIP_CODE_78: // Isolated star-like snow crystals (with or without fog)
		case WMO_SOLID_PERCIP_CODE_79: // Ice pellets
		case WMO_SHOWER_CODE_80: // Rain shower(s), slight
		case WMO_SHOWER_CODE_81: // Rain shower(s), moderate or heavy
		case WMO_SHOWER_CODE_82: // Rain shower(s), violent
		case WMO_SHOWER_CODE_83: // Shower(s) of rain and snow mixed, slight
		case WMO_SHOWER_CODE_84: // Shower(s) of rain and snow mixed, moderate or heavy
		case WMO_SHOWER_CODE_85: // Snow shower(s), slight
		case WMO_SHOWER_CODE_86: // Snow shower(s), moderate or heavy
		case WMO_SHOWER_CODE_87: // Shower(s) of snow pellets or small hail, with or without rain or rain and snow mixed, slight
		case WMO_SHOWER_CODE_88: // Shower(s) of snow pellets or small hail, with or without rain or rain and snow mixed, moderate or heavy
		case WMO_SHOWER_CODE_89: // Shower(s) of hail*, with or without rain or rain and snow mixed, not associated with thunder, slight
		case WMO_SHOWER_CODE_90: // Shower(s) of hail*, with or without rain or rain and snow mixed, not associated with thunder, moderate or heavy
		case WMO_SHOWER_CODE_91: // Slight rain at time of observation, Thunderstorm during the preceding hour but not at time of observation
		case WMO_SHOWER_CODE_92: // Moderate or heavy rain at time of observation, Thunderstorm during the preceding hour but not at time of observation
		case WMO_SHOWER_CODE_93: // Slight snow, or rain and snow mixed or hail** at time of observation, Thunderstorm during the preceding hour but not at time of observation
		case WMO_SHOWER_CODE_94: // Moderate or heavy snow, or rain and snow mixed or hail** at time of observation, Thunderstorm during the preceding hour but not at time of observation
		case WMO_SHOWER_CODE_95: // Thunderstorm, slight or moderate, without hail** but with rain and/or snow at time of observation, Thunderstorm at time of observation
		case WMO_SHOWER_CODE_96: // Thunderstorm, slight or moderate, with hail** at time of observation, Thunderstorm at time of observation
		case WMO_SHOWER_CODE_97: // Thunderstorm, heavy, without hail** but with rain and/or snow at time of observation, Thunderstorm at time of observation
		case WMO_SHOWER_CODE_98: // Thunderstorm combined with duststorm or sandstorm at time of observation, Thunderstorm at time of observation
		case WMO_SHOWER_CODE_99: // Thunderstorm, heavy, with hail** at time of observation, Thunderstorm at time of observation
	default:
		break;
	}

	return 1;
}