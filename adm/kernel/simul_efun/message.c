// message.c
// Update by Doing
// Update by Lonely


string sort_msg(string input)
{
#ifdef BINARY_SUPPORT
        return efun::sort_string(input, 60, 0);
#else
        int i;
        int sl;
        int len;
        int esc;
        string result;
        result = "";

        len = 0;
        esc = 0;
        sl = strlen(input);
        for( i = 0; i < sl; i++ ) {
                if( len >= 64 && input[i] != '\n' ) {
                        switch (input[i..i+1])
                        {
                        case "：":
                        case "”":
                        case "。":
                        case "，":
                        case "、":
                        case "；":
                        case "）":
                        case " )":
                        case "！":
                        case "？":
                                break;
                        default:
                                len = 0;
                                result += "\n";
                                break;
                        }
                }

                if( input[i] == 27)
                        esc = 1;

                if( !esc ) {
                        if( input[i] > 160 ) {
                                result += input[i..i+1];
                                i ++;
                                len += 2;
                                continue;
                        }
                        if( input[i] == '\n' ) {
                                result += "\n";
                                len = 0;
                                continue;
                        }
                }

                result += input[i..i];
                if( !esc ) len++;

                if( esc && input[i] == 'm' )
                        esc = 0;
        }

        if( i < sl )
                result += input[i..sl-1];

        return result;
#endif
}

varargs void message_vision(string msg, object me, object you)
{
        string my_gender, your_gender, my_name, your_name;
        string str1, str2, str3;

        if( !objectp(me) || !environment(me) ) return;

        my_name = me->name();
        my_gender = query("gender", me);

        str1 = replace_string(msg,  "$P", gender_self(my_gender));
        str1 = replace_string(str1, "$N", gender_self(my_gender));
        str3 = replace_string(msg,  "$P", my_name);
        str3 = replace_string(str3, "$N", my_name);

        if( you ) {
                your_name = you->name();
                your_gender = query("gender", you);
                str1 = replace_string(str1, "$p", gender_pronoun(your_gender));
                str1 = replace_string(str1, "$n", your_name);

                str3 = replace_string(str3, "$p", your_name);
                str3 = replace_string(str3, "$n", your_name);

                str2 = replace_string(msg,  "$P", gender_pronoun(my_gender));
                str2 = replace_string(str2, "$p", gender_self(your_gender));
                str2 = replace_string(str2, "$N", my_name);
                str2 = replace_string(str2, "$n", gender_self(your_gender));
                message("vision", str2, you);
        }

        message("vision", str1, me);
        if( !environment(me) ) return;
        message("vision", str3, all_inventory(environment(me)), ({ me, you }));
        if( query("fight_room", environment(me)) ) // 擂台比武直播
                environment(me)->relay_message(str3);
}

varargs void message_sort(string msg, object me, object you)
{
        string my_gender, your_gender, my_name, your_name;
        string str1, str2, str3;

        if( !objectp(me) || !environment(me) ) return;

        my_name= me->name();
        my_gender = query("gender", me);
        str1 = replace_string(msg,  "$P", gender_self(my_gender));
        str1 = replace_string(str1, "$N", gender_self(my_gender));
        str3 = replace_string(msg,  "$P", my_name);
        str3 = replace_string(str3, "$N", my_name);
        if( you ){
                your_name= you->name();
                your_gender= query("gender", you);
                str2 = replace_string(msg,  "$P", gender_pronoun(my_gender));
                str2 = replace_string(str2, "$p", gender_self(your_gender));
                str2 = replace_string(str2, "$N", my_name);
                str2 = replace_string(str2, "$n", gender_self(your_gender));
                message("vision", sort_msg(str2), you);
                str1 = replace_string(str1, "$p", gender_pronoun(your_gender));
                str1 = replace_string(str1, "$n", your_name);
                str3 = replace_string(str3, "$p", your_name);
                str3 = replace_string(str3, "$n", your_name);
        }
        message("vision", sort_msg(str1), me);
        message("vision", sort_msg(str3),  environment(me), ({ me, you}) );
}

/* Definition of the level of showing combat message */
#define SHOW_ALL                0
#define SHOW_DAMAGE             1
#define SHOW_BRIEF_DAMAGE       2
#define SHOW_BRIEF_SELF_DAMAGE  3
#define SHOW_NONE               4

varargs void message_combatd(string msg, object me, object you, string damage_info)
{
        string my_gender, your_gender, my_name, your_name;
        string str1, str2, str3f, str3d;
        mixed my_flag;
        mixed your_flag;
        int damage_flag;
        int brief;
        int others;
        object ob;
        object *obs;

        if( !objectp(me) || !environment(me) ) return;

        brief = 1;
        if( !stringp(damage_info) ) {
                // No damage_info defined, so I must show full message.
                damage_info = "";
                brief = 0;
                msg = "\n" + msg;
        }

        damage_flag = (strlen(damage_info) > 0);

        my_name= me->name();
        my_gender = query("gender", me);

        if( you ) {
                your_name = you->name();
                your_gender = query("gender", you);
        }

        if( userp(me) ) {
                if( !brief) my_flag = SHOW_ALL;
                else {
                        my_flag = query("env/combatd", me);
                        if( stringp(my_flag) && my_flag == "YES" ) my_flag = SHOW_BRIEF_DAMAGE;
                        if( !intp(my_flag) ) my_flag = SHOW_ALL;
                }

                if( my_flag >= SHOW_BRIEF_SELF_DAMAGE || my_flag && !damage_flag ) {
                        if( !stringp(str1 = query("env/ignore_combat", me)) )
                                str1 = "";
                        else
                                str1 += "\n";
                } else
                if( my_flag == SHOW_BRIEF_DAMAGE )
                        str1 = (string)damage_info;
                else
                        str1 = msg + (string)damage_info;

                str1 = replace_string(str1, "$P", gender_self(my_gender));
                str1 = replace_string(str1, "$N", gender_self(my_gender));
                if( you ) {
                        str1 = replace_string(str1, "$p", gender_pronoun(your_gender));
                        str1 = replace_string(str1, "$n", your_name);
                }

                if( strlen(str1) > 0 )
                        message("tell_object", str1, me);
        }

        if( you && userp(you) ) {
                if( !brief ) your_flag = SHOW_ALL;
                else {
                        your_flag = query("env/combatd", you);
                        if( stringp(your_flag) && your_flag == "YES" ) your_flag = SHOW_BRIEF_DAMAGE;
                        if( !intp(your_flag) ) your_flag = SHOW_ALL;
                }

                if( your_flag == SHOW_ALL || damage_flag && your_flag < SHOW_NONE ) {
                        if( your_flag <= SHOW_DAMAGE )
                                str2 = msg + (string)damage_info;
                        else
                                str2 = (string)damage_info;

                        str2 = replace_string(str2, "$P", gender_pronoun(my_gender));
                        str2 = replace_string(str2, "$p", gender_self(your_gender));
                        str2 = replace_string(str2, "$N", my_name);
                        str2 = replace_string(str2, "$n", gender_self(your_gender));
                        if( strlen(str2) > 0)
                                message("tell_object", str2, you);
                }
        }
        // 擂台比武直播
        if( query("fight_room", environment(me)) ) {
                str3f = msg;
                str3d = (string)damage_info;
                str3f = replace_string(str3f, "$P", my_name);
                str3f = replace_string(str3f, "$N", my_name);
                str3d = replace_string(str3d, "$P", my_name);
                str3d = replace_string(str3d, "$N", my_name);
                if( you ) {
                        str3f = replace_string(str3f, "$p", your_name);
                        str3f = replace_string(str3f, "$n", your_name);
                        str3d = replace_string(str3d, "$p", your_name);
                        str3d = replace_string(str3d, "$n", your_name);
                }
                str3f += str3d;
                environment(me)->relay_message(str3f);
        }

        obs = filter_array(all_inventory(environment(me)),
                           (: (userp($1) && !query("env/combat_brief", $1)) || $1->want_receive_msg() :)) -
              ({ me, you });
        others = sizeof(obs);
        if( others ) {
                str3f = msg;
                str3d = (string)damage_info;
                str3f = replace_string(str3f, "$P", my_name);
                str3f = replace_string(str3f, "$N", my_name);
                str3d = replace_string(str3d, "$P", my_name);
                str3d = replace_string(str3d, "$N", my_name);
                if( you ) {
                        str3f = replace_string(str3f, "$p", your_name);
                        str3f = replace_string(str3f, "$n", your_name);
                        str3d = replace_string(str3d, "$p", your_name);
                        str3d = replace_string(str3d, "$n", your_name);
                }

                if( brief )
                        str3f += str3d;
                else
                        // no damage info, so I must show all the message info
                        str3d = str3f;

                if( strlen(str3f) < 1 )
                        return;

                foreach (ob in obs ) {
                        switch (query("env/combatd", ob))
                        {
                        case SHOW_NONE:
                                break;

                        case SHOW_BRIEF_DAMAGE:
                        case SHOW_BRIEF_SELF_DAMAGE:
                                message("tell_object", str3d, ob);
                                break;

                        default:
                                message("tell_object", str3f, ob);
                                break;
                        }
                }
        }
}

varargs void tell(mixed target, string msg, string classes)
{

        if( !stringp(classes) ) classes = "tell_object";
        message(classes, msg, target);
        //
        //if( objectp(target) || arrayp(target) )
        //        target->catch_tell(msg, classes);
     
}
void tell_object(object ob, string str)
{
        message("tell_object", str, ob);
}

void tell_team(object *obs, string str)
{
        foreach( object ob in obs )
                tell_object(ob, str);
}

varargs void tell_room(mixed ob, string str, object *exclude)
{
        if( ob ) message("tell_room", str, ob, exclude);
}

void shout(string str)
{
        message("shout", str, users(), this_player());
}

void write(string str)
{
        if( this_player() )
                message("write", str, this_player());
        else if( previous_object() )
                message("write", str, previous_object());
        else
                efun::write(str);
}

varargs void say(string str, mixed exclude)
{
        if( living(previous_object()) )
                message("say", str, environment(previous_object()), previous_object());
        else if( this_player() )
                message("say", str, environment(this_player()), this_player());
}

void message(mixed arg, string message, mixed target, mixed exclude)
{
        efun::message(arg, message, target, exclude);
}

void message_system(string message)
{
        message("system", HIW "\n【系统】" + message + "\n" NOR,
                all_interactive(), 0);
}

int notify_fail(string msg)
{
        if( this_player() ) {
                set_temp("notify_fail", msg, this_player());

                if( query_temp("big5", this_player()) )
#ifdef LONELY_IMPROVED
                        // msg = G2B(msg);
                        msg = LANGUAGE_D->toBig5(msg);
#else
                        msg = LANGUAGE_D->toBig5(msg);
#endif
                return efun::notify_fail(ESC "[256D" ESC "[K" + msg);
        } else
                return 0;
}

string query_fail_msg()
{
        return query_temp("notify_fail", this_player());
}


// 统一代名词转换之讯息发送函式
varargs void msg(string msg, object me, object you, int onlooker, string classes, object *exclude, mapping translate)
{
        string my_msg, your_msg;
        string my_idname, your_idname;

        if( !msg || !objectp(me) ) return;

        // 取得 Me 物件资料

       my_idname = me->query_idname() || "无名称";


        // 额外输入关键字之转换, 即除了 $ME 与 $YOU 以外之转换
        if( mapp(translate) )
                foreach(string pattern, string replace in translate)
                msg = replace_string(msg, pattern, replace);

        // Me 讯息之第二人称转换
        my_msg = replace_string(msg, "$ME", pnoun(2, me));

        // 若有对象物件 you, 则对 you 作讯息处理
        if( objectp(you) )
        {
                your_idname = you->query_idname() || "无名称";

                // Me 讯息之第三人称转换
                my_msg = replace_string(my_msg, "$YOU", your_idname, 1);
                my_msg = replace_string(my_msg, "$YOU", pnoun(3, you));

                // You 讯息之第二人称转换
                your_msg = replace_string(msg, "$ME", my_idname, 1);
                your_msg = replace_string(your_msg, "$ME", pnoun(3, me));
                your_msg = replace_string(your_msg, "$YOU", pnoun(2, you));


                // 对物件 you 送出讯息
                if( !arrayp(exclude) || member_array(you, exclude) == -1 )
                        tell(you, your_msg, classes);
        }

        // 对物件 Me 送出讯息
        if( !arrayp(exclude) || member_array(me, exclude) == -1 )
                tell(me, my_msg, classes);

        // 若有 onlooker(旁观者) 参数, 则对与 me 或 you 同一环境中的生物发出讯息
        if( onlooker )
        {
                string onlookers_msg;
                object *onlookers = present_objects(me)||({});

                if( environment(me)->is_character() )
                        onlookers += ({ environment(me) });

                if( objectp(me) && wizardp(me) && query("no_msg_looker", me) && objectp(you) ) return;
                if( objectp(you) && wizardp(you) && query("no_msg_looker", you) ) return;

                if( objectp(you) && environment(me) != environment(you) ) 
                {
                        onlookers += present_objects(you)||({});
                        if( objectp(environment(you)) && environment(you)->is_character() )
                                onlookers += ({ environment(you) });
                }

                onlookers -= ({ me, you }) + (exclude || ({}));

                onlookers_msg = replace_string(msg, "$ME", my_idname);

                if( objectp(you) ) 
                        onlookers_msg = replace_string(onlookers_msg, "$YOU", your_idname);

                // 对所有旁观者物件送出讯息
                tell(onlookers, onlookers_msg, classes);
        }
}

