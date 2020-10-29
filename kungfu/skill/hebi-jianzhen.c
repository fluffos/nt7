// shuangjian-hebi.c
// 双剑合壁剑阵

inherit SKI_ZHEN;

void create() 
{
        ::create(); 

        set_menpai("古墓派");            // 阵法所属门派 
        set_member_num(2);               // 阵形人数 
        set_array_name("双剑合壁剑阵");  // 阵法名称 
        set_master_level(100);           // 阵主要求此阵法的最低等级 
        set_member_level(50);            // 阵法成员要求此阵法的最低等级 
        set_skill_type("yunv-jian");     // 阵法所使用的武功 
        set_master_skill_level(100);     // 阵主武功等级 
        set_member_skill_level(50);      // 成员武功等级 
        set_effective_level(10);         // 阵法有效值 
}