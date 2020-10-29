#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIW "字条" NOR, ({ "zi tiao", "zi", "tiao" }));
        set_weight(50);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "张");
                set("long", HIC "这是一张字条，上书：\n\n" HIW
                                 "   世间万物皆为幻，吾本亦为幻，君既已决定背弃今生，切勿再被\n"
                                 "今生幻想所困！纵有万语，君梦将醒，方尽矣！来生多珍重！！！\n\n"
                                 "                                                      ---- 梦·无名\n\n" NOR);
                set("value", 300);
                set("material", "paper");
        }
}
