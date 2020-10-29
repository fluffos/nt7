// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猪小鸟[2;37;0m[2;37;0m", ({"zzjjll"}));        
        set("gender", "男性");                
        set("long", "小鸟飞[2;37;0m
它是小花花的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hmjhs");
        set("owner_name", "小花花");
        set_temp("owner", "hmjhs");
        set_temp("owner_name", "小花花");
        ::setup();
}
