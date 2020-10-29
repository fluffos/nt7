// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小鸡[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "一只小鸡哦[2;37;0m
它是北城香的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "btx");
        set("owner_name", "北城香");
        set_temp("owner", "btx");
        set_temp("owner_name", "北城香");
        ::setup();
}
