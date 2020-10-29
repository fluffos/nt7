//Obj: /d/ruzhou/npc/obj/xitie.c  喜贴，参加婚宴的请柬
// llm 99/07

inherit ITEM;

void create()
{
        set_name("喜帖", ({ "xi tie","tie"}));
        set_weight(500);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/
   {
                set("unit", "张");
                set("long","一张大红的帖子，上面写着：\n"
                        "诚邀阁下参加我们的在汝州红娘庄的婚礼和汝州迎宾楼的婚宴。\n");
      set("material", "paper");
        }
        setup();
}