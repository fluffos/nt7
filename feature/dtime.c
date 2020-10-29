/****************************
 * dtime.c                  *
 * 控制物件定时出现在房间里 *
 * 定义为： F_DTIME         *
 *                          *
 * by Find.                 *
 ****************************/

class time
{
        int start_day;
        int stop_day;
        int start_sec;
        int stop_sec;
}

nosave class time *dtime = ({});
nosave string disappear_msg;

protected int parse_string(string str, int ref day, int ref sec);
nomask int is_time_ctl_ob() { return 1; }

nomask void set_disappear_msg(string arg)
{
        if( !stringp(arg) || (arg == "") )
                return ;
        disappear_msg = arg;
}

nomask string query_disappear_msg()
{
        if( stringp(disappear_msg) )
                return disappear_msg;

        if( this_object()->is_character() )
                return sprintf("%s匆匆忙忙的走了。\n",this_object()->name());
        else
                return sprintf("%s慢慢的消失了。\n",this_object()->name());
}

/********************************************
 * 时间设置格式：
 *      mapping time = ([
 *              time_start1 : time_stop1,
 *              time_start2 : time_stop2,
 *              ...,
 *              ...,
 *              ...
 * ])
 *********************************************/
nomask void set_appear_time(mapping t)
{
        if( !mapp(t) || !sizeof(t) )
                error("F_DTIME: 无时间格式设置。\n");

        foreach(string start, string stop in t) {
                class time temp;
                int n;

                temp = new(class time);

                if( !parse_string(start, ref temp->start_day, ref temp->start_sec)
                ||  !parse_string(stop, ref temp->stop_day, ref temp->stop_sec) )
                        error("F_DTIME: 时间格式错误。\n");

                if( abs(temp->start_day) > abs(temp->stop_day) ) {
                        n = temp->start_day;
                        temp->start_day = temp->stop_day;
                        temp->stop_day = n;
                }

                if( temp->start_day && !temp->stop_day ) {
                        if( temp->start_day < 0 )
                                temp->stop_day = -31;
                        else
                                temp->stop_day = 365;
                }

                if( !temp->start_day && temp->stop_day ) {
                        if( temp->stop_day < 0 )
                                temp->start_day = -1;
                        else
                                temp->start_day = 1;
                }

                if( ((temp->start_day < 0) && (temp->stop_day >= 0))
                ||  ((temp->start_day >= 0) && (temp->stop_day < 0)) )
                        error("F_DTIME: 时间格式错误。\n");

                if( temp->stop_sec == 1 )
                        temp->stop_sec = 1440;

                dtime += ({ temp });
        }

        if( !this_object()->is_character() )
                call_out("check_self", 5);
}

protected int parse_string(string str, int ref day, int ref sec)
{
        string s1,s2,s3;
        int m,d;
        int *month_begin = ({1,32,60,91,121,152,182,213,244,274,305,335});
        int *days_per_month = ({ 31,28,31,30,31,30,31,31,30,31,30,30 });

        if( !stringp(str) || (str == "") )
                return 0;

        if( sscanf(str,"%s,%s,%s",s1,s2,s3) != 3 )
                return 0;

        if( s1 == "" )
                m = 0;
        else
                m = atoi(s1);

        if( (m < 1) || (m > 12) )
                m = 0;


        if( s2 == "" )
                d = 0;
        else
                d = atoi(s2);

        if( (d < 1) || (d > 31) )
                d = 0;

        if( s3 == "" )
                sec = 0;
        else {
                sec = atoi(s3);
                if( sec < 1 )
                        sec = 1;
                else if( sec > 1440 )
                        sec = 1440;
        }

        if( !m && !d && !sec )
                return 0;

        if( m ) {
                day = month_begin[m-1];
                if( d ) {
                        if( d > days_per_month[m-1] )
                                d = days_per_month[m-1];
                        day += d - 1;
                }
        }
        else {
                if( d )
                        day = -d;
        }

        return 1;
}

nomask int query_is_valid_time()
{
        int dm,d,s;

        if( !sizeof(dtime) )
                error("F_DTIME: 无时间格式设置。\n");

        dm = this_object()->query_day_in_month();
        d = this_object()->query_day();
        s = this_object()->query_time();

        foreach(class time temp in dtime) {
                int n;

                if( temp->start_day ) {
                        if( temp->start_day < 0 )
                                n = dm;
                        else
                                n = d;

                        if( (n >= abs(temp->start_day)) && (n <= abs(temp->stop_day)) ) {
                                if( !temp->start_sec )
                                        return 1;
                                else if( (s >= temp->start_sec) && (s <= temp->stop_sec) )
                                        return 1;
                        }
                }
                else if( (temp->start_sec > temp->stop_sec) && ( (s >= temp->start_sec) || (s <= temp->stop_sec) ) )
                        return 1;
                else if( (temp->start_sec < temp->stop_sec) && (s >= temp->start_sec) && (s <= temp->stop_sec) )
                        return 1;
        }

        return 0;
}

nomask int query_lasting_time()
{
        int m,md,yd,s,lasting;
        int *days_per_month = ({ 31,28,31,30,31,30,31,31,30,31,30,30 });

        if( !sizeof(dtime) )
                error("F_DTIME: 无时间格式设置。\n");

        m = this_object()->query_month();
        md = this_object()->query_day_in_month();
        yd = this_object()->query_day();
        s = this_object()->query_time();

        foreach(class time temp in dtime) {
                int i;

                if( temp->start_day ) {
                        if( temp->start_day < 0 ) {
                                if( md <= abs(temp->start_day) )
                                        i = (abs(temp->start_day) - md)*1440;
                                else
                                        i = (days_per_month[m-1]-md + abs(temp->start_day))*1440;
                        }
                        else {
                                if( yd <= temp->start_day )
                                        i = (temp->start_day - yd)*1440;
                                else
                                        i = (365 - yd + temp->start_day)*1440;
                        }
                }

                if( s <= temp->start_sec )
                        i += temp->start_sec - s;
                else
                        i += 1440 - s + temp->start_sec;

                if( i <= 1 )
                        i = 1;

                if( !lasting || (lasting > i) )
                        lasting = i;
        }

        return lasting;
}

protected nomask void check_self()
{
        object env;

        if( !query_is_valid_time() ) {
                if( objectp(env = environment()) ) {
                        tell_object(env,query_disappear_msg());
                        env->set_check_dtime(query_lasting_time());
                }
                destruct(this_object());
        }

        else
                call_out("check_self", 10);
}
