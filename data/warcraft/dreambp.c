// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m爱犬小白[2;37;0m[2;37;0m", ({"mydog"}));        
        set("gender", "男性");                
        set("long", "梦旅人现实生活中的爱犬，2013年2月离开了世界，享年8岁。[2;37;0m
它是梦旅人的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dreambp");
        set("owner_name", "梦旅人");
        set_temp("owner", "dreambp");
        set_temp("owner_name", "梦旅人");
        ::setup();
}
