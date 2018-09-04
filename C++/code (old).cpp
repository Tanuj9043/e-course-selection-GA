#include <bits/stdc++.h>
#include <cstring>
using namespace std;

#define FIO ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mp(x, y) make_pair(x, y)
#define set(p) memset(p, -1, sizeof(p))
#define clr(p) memset(p, 0, sizeof(p))
#define mem(p, v) memset(p, v, sizeof(p))
#define all(v) v.begin(),v.end()
#define ff first
#define ss second
#define ll long long
#define ull unsigned long long
#define ld long double
#define vv(x) vector<x >
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof  pop_front
#define umap(x,y) unordered_map<x,y >
#define pq priority_queue
#define pp(x) pair<x, x >
#define fori(i,n) for(int i=0; i<n; i++)
#define forl(i,n) for(ll i=0; i<n; i++)
#define tr(it,c) for(auto it=c.begin(); it!=c.end(); it++)
#define file freopen("inp.in","r",stdin); freopen("outp.out","w",stdout)

const double pi = acos(-1.0);
const int imax = 2147483647;
const int imin = -2147483647;
const ll lmax = 9223372036854775807;
const ll lmin = -9223372036854775807;

class course{
public:
    string name;

    ll interest, cost, time, prerequisite, teacher_expertise,
    student_pursue, rating, content_quality, doubt_clearance,
    mentors, projects, access_time;

    bool on_demand_video, device_compatible, certificate,
    downloadable_resource;

    course(){
        interest=cost=time=prerequisite=teacher_expertise=
        student_pursue=rating=content_quality=doubt_clearance=
        mentors=projects=access_time=0;

        on_demand_video=device_compatible=certificate=downloadable_resource=false;
    }

    /*
    bool valid(){
        return (
            interest>=1 && interest<=10 &&
            cost>=5000 &&
            time>=1 &&
            prerequisite>=1 && prerequisite<=10 &&
            teacher_expertise>=1 && teacher_expertise<=10 &&
            student_pursue>=1 &&
            rating>=1 && rating<=10 &&
            content_quality>=1 && content_quality<=10 &&
            doubt_clearance>=1 && doubt_clearance<=10 &&
            mentors>=1 &&
            projects>=0 &&
            access_time>=0
        );
    }
    */

    double fitness(){
        double f = 0;

        f += 16.0 * interest;
        f += 15.0 * ((4000.0/(double)cost)*10.0);
        f += 14.0 * ((2.0/(double)time)*10.0);
        f += 13.0 * rating;
        f += 12.0 * (((double)student_pursue/10.0)*10.0);
        f += 11.0 * teacher_expertise;
        f += 10.0 * ((5.0/(double)prerequisite)*10.0);
        f += 9.0  * content_quality;
        f += 8.0  * (device_compatible==true);
        f += 7.0  * doubt_clearance;
        f += 6.0  * (downloadable_resource==true);
        f += 5.0  * (on_demand_video==true);
        f += 4.0  * (((double)projects/2.0)*10.0);
        f += 3.0  * (certificate==true);
        f += 2.0  * (((double)access_time/6.0)*10.0);
        f += 1.0  * (((double)mentors/2.0)*10.0);

        return f;
    }

    void printCourse(){
        cout<<"============================="<<name<<"===============================\n";
        cout<<"Interest               : "<<interest<<"\n";
        cout<<"Cost                   : "<<cost<<"\n";
        cout<<"Time                   : "<<time<<" months\n";
        cout<<"Rating                 : "<<rating<<"\n";
        cout<<"Students pursuing      : "<<student_pursue<<"\n";
        cout<<"Tearcher's Expertise   : "<<teacher_expertise<<"\n";
        cout<<"Prerequisite           : "<<prerequisite<<"\n";
        cout<<"Content                : "<<content_quality<<"\n";
        cout<<"Device Compatibility   : "<<(device_compatible ? "Yes" : "No")<<"\n";
        cout<<"Doubt clearance        : "<<doubt_clearance<<"\n";
        cout<<"Downloadable resources : "<<(downloadable_resource ? "Yes" : "No")<<"\n";
        cout<<"On-Demand Videos       : "<<(on_demand_video ? "Yes" : "No")<<"\n";
        cout<<"Projects               : "<<projects<<"\n";
        cout<<"Certificate            : "<<(certificate ? "Yes" : "No")<<"\n";
        cout<<"Accessibility Time     : "<<access_time<<" months\n";
        cout<<"Mentors                : "<<mentors<<"\n";
        cout<<"========================Fitness = "<<fitness()<<"===========================\n\n\n";
    }
};

int main(){
	///file;

    ofstream fa("graph.csv");
    fa<<"Generation,Fitness"<<endl;

	srand ( time(NULL) );
    ll population = 100;
    ll courses = 20;

    pair<course,ll> p[population][courses];

    fori(j,courses){
        course c;

        c.name = "Course " + to_string(j+1);
        c.interest = rand()%10 + 1;
        c.cost = rand()%9001 + 1000;
        c.time = rand()%3 + 1;
        c.prerequisite = rand()%10 + 1;
        c.teacher_expertise = rand()%10 + 1;
        c.student_pursue = rand()%25 + 1;
        c.rating = rand()%10 + 1;
        c.content_quality = rand()%10 + 1;
        c.doubt_clearance = rand()%10 + 1;
        c.mentors = rand()%3 + 1;
        c.on_demand_video = rand()%2;
        c.device_compatible = rand()%2;
        c.certificate = rand()%2;
        c.projects = rand()%5+1;
        c.downloadable_resource = rand()%2;
        c.access_time = rand()%9 + 3;

        ///c.printCourse();

        fori(i,population){
            p[i][j].ss = rand()%2;
            p[i][j].ff = c;
        }
    }

	vector<pair<double,int> > v;
    fori(gen,1000){
		v.clear();

        ///cout<<"==========================GENERATION "<<(gen+1)<<"===============================\n";

        double fitness, cost, time, maxFit=imin, fitAvg;
        int ind=-1;
        fori(i,population){
            fitness = cost = time = 0;
            fori(j,courses){
                if(p[i][j].ss==1){
					///printf("1 ");
                    fitness += p[i][j].ff.fitness();
                    cost += p[i][j].ff.cost;
                    time += p[i][j].ff.time;
                }
                ///else printf("1 ");
            }

            /*
			printf("Cost = %lf\nTime = %lf\n",cost,time);
			printf("Fitness Factor : %lf\n",(fitness/courses)/10.0);
			printf("Cost Factor    : %lf\n",6.0 * ((45000.0/(double)cost)*10.0));
			printf("Time Factor    : %lf\n\n",4.0 * ((12.0/(double)time)*10.0));
			*/

            fitness += (fitness/courses)/10.0;
            if(cost!=0) fitness += 6.0  * ((40000.0/(double)cost)*10.0);
			if(time!=0) fitness += 4.0  * ((12.0/(double)time)*10.0);

			v.pb(mp(fitness,i));

			///printf("\tFitness = %f\n",fitness);
            fitAvg+=fitness;
        }
        ///cout<<fitAvg<<endl;
		fitAvg/=population;
		///printf("%d, %lf\n",gen,fitAvg);
        fa<<gen<<","<<fixed<<setprecision(5)<<fitAvg<<endl;

        ///cout<<"======================================================================\n\n\n";

        sort(all(v));

        ///CROSS-OVER
        for(int k=0; k<(1*v.size())/10; k+=2){
			int i=v[k].ss, j=v[k+1].ss;
			int x = rand()%courses;
            int y = rand()%(courses-x) + x;
            for(int l=x; l<=y; l++){
                swap(p[i][l].ss, p[j][l].ss);
            }
        }

        ///MUTATION
        fori(i,population){
            int z = rand()%1000 + 1;
            if(z<=5){
                int x = rand()%courses;
                p[i][x].ss = 1 - p[i][x].ss;
            }
        }
    }
    return 0;
}
