#include <ansi.h>
inherit NPC;

#define GAOSHOU_DIR "/data/gaoshou/"

void init_npc();
int is_c_file(string arg);                //判断arg是否*.c文件格式
string do_perform(string perform_skill);
string auto_perform();

object my_enemy;

int is_player() { return 1; }

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
        string id;

        id = query("id");
        if (! stringp(id)) return 0;
        return sprintf(GAOSHOU_DIR "npc/%s_xr", id);
}

int save()
{
        return 0;
}

int restore()
{
        string file;

        if (stringp(file = this_object()->query_save_file()))
                return restore_object(file);
        return 0;
}

void create()
{
        string id;

        ::create();
        id = XINRUI_D->query_top_id();
        if( !id ) id = "test";
        set_name( "泥潭新锐" , ({ id }) );
        setup();        

        restore();
        reset_action();
        call_out("init_npc", 2);
}

void init_npc()
{
        object me, cloth, weapon;
        mapping summon_ob;
        string *carry_ob, *summon_key, weapon_file;
        int i;

        me = this_object();

        if( mapp(summon_ob=query("can_summon", me)) && sizeof(summon_ob) )
        {
                summon_key = keys(summon_ob);
                for(i = 0;i < sizeof(summon_key);i++)
                {
                        if (! stringp(weapon_file = summon_ob[summon_key[i]]))
                                continue;
                        if (file_size(weapon_file) < 0)
                                continue;
                        call_other(weapon_file, "???");
                        weapon = find_object(weapon_file);
                        if (! weapon || ! weapon->receive_summon(me))
                        {
                               message_vision(HIM "$N" HIM "扬起手来，口中念念有"
                                       "词。\n然而什么也没有发生 :)\n", me);
                        } else
                               set("value", 0, weapon);
                }
        }
        if( arrayp(carry_ob=query("carry_ob", me)) && sizeof(carry_ob) )
        {
                for(i = 0;i < sizeof(carry_ob);i++)
                {
                        if (objectp(cloth = new(carry_ob[i])))
                        {
                                cloth->move(me);
                                set("value", 0, cloth);
                        }
                }
        }
        command("wear all");
        command("wield all");
        command("yun powerup");
        command("yun shield");
        switch (me->query_skill_mapped("force"))
        {
                case "linji-zhuang":
                        command("yun tiandi");
                        command("yun daxiao");
                        set("qi",query("max_qi",  me), me);
                        set("jing",query("max_jing",  me), me);
                        break;
                case "huagong-dafa":
                        command("yun hua");
                        break;
                case "zixia-shengong":
                        command("yun ziqi");
                        break;
                case "huntian-qigong":
                        command("yun haixiao");
                        command("yun shengang");
                        break;
                case "bibo-shengong":
                        command("yun wuzhuan");
                        break;
                case "yunv-xinfa":
                        command("yun wang");
                        break;
                case "nuhai-kuangtao":
                        command("yun haixiao");
                        break;
                case "xiantian-gong":
                        command("yun chunyang");
                        break;
                case "longxiang":
                        command("yun longxiang");
                        command("yun panlong");
                        command("yun tunxiang");
                        break;
                case "hamagong":
                        command("yun reserve");
                        break;
                case "lengyue-shengong":
                        command("yun freeze");
                        break;
                case "kurong-xinfa":
                        command("yun kurong");
                        break;
        }
}

void kill_ob(object ob) 
{
        if (auto_perform() != "VOID")
        {
                ::kill_ob(ob);
                start_busy(0);
                call_other(auto_perform(), "perform", this_object(), ob);
                return;
        }
        return ::kill_ob(ob);
}
        
int is_c_file(string arg)                //判断arg是否*.c文件格式
{
        int l;
        l = strlen(arg);
        if (arg[l - 1] == 'c' && arg[l - 2] == '.')
                return 1;
        return 0;
}

//      auto_perform()
//      自动出绝招
string do_perform(string perform_skill)
{
        int l;
        string dir;
        string file;
        mixed *all_file;

        if (! stringp(dir = SKILL_D(perform_skill) + "/") || file_size(dir) != -2)        //这个武功没有绝招
        return "VOID";

        if (file_size(dir + "perform/") == -2)        //这个武功有一个perform/子目录
                dir += "perform/";

        all_file = get_dir(dir);

        if (!sizeof(all_file))        //这个武功没有绝招
                return "VOID";

        all_file = filter_array(all_file,(: is_c_file :));        //取出*.c文件
        if (!sizeof(all_file))        //这个武功没有绝招
                return "VOID";

        file = all_file[random(sizeof(all_file))];        //随机抽取武功的绝招
        l = strlen(file);
        file = dir + file[0..l-3];
        return file;
}

string auto_perform()
{
        object me,weapon;
        string askill,the_pfm;
        mapping prepare;
        mapping my_temp;
        int can_auto_perform;        
        string the_perform_skill,perform_skill_1,perform_skill_2;

        me = this_object();
        if (! living(me)) return "VOID";

        if (! mapp(my_temp = me->query_entire_temp_dbase()))
                my_temp = ([ ]);
        
        prepare = me->query_skill_prepare();
        if (weapon = my_temp["weapon"])
                askill=query("skill_type", weapon);
        else if (! prepare || sizeof(prepare) == 0) askill = "unarmed";
        else if (sizeof(prepare)) askill = (keys(prepare))[0];
        if (askill == "pin") askill = "sword";

        askill = me->query_skill_mapped(askill);

        can_auto_perform = 0;
        if (askill)
        { 
                perform_skill_1 = askill;        //第一种pfm;
                can_auto_perform = 1;
        }
        //如果没有装备兵器，而且又有空手武功bei了，那么取第一种bei的空手武功的绝招为第二种pfm;
        if (!weapon && prepare && sizeof(prepare) > 1) 
                perform_skill_2 = me->query_skill_mapped((keys(prepare))[1]); 

        if (perform_skill_2) can_auto_perform = 2;
        if (can_auto_perform == 1)
                return do_perform(perform_skill_1);
        else if (can_auto_perform == 2)
        {
                //随机选择两种PFM
                if (random(2))
                        the_perform_skill = perform_skill_1;
                else
                        the_perform_skill = perform_skill_2;

                the_pfm = do_perform(the_perform_skill);
                if (the_pfm == "VOID")
                        the_pfm = do_perform((the_perform_skill == perform_skill_1) ? 
                                                perform_skill_2 : perform_skill_1);
                return the_pfm;
        } else return "VOID";
}