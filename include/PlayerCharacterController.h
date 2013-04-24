#ifndef __Player_H__
#define __Player_H__

#include "Ogre.h"
#include "OIS.h"
#include "OgreTagPoint.h"
#include "MovableText.h"
#include <string.h>
using namespace Ogre;

#define NUM_ANIMS 13//13           // number of animations the character has
#define CHAR_HEIGHT 5          // height of character's center of mass above ground
#define CAM_HEIGHT 30           // height of camera above character's center of mass
#define RUN_SPEED 40          // character running speed in units per second
#define WALK_SPEED 25
#define TURN_SPEED 500.0f      // character turning in degrees per second
#define ANIM_FADE_SPEED 7.5f   // animation crossfade speed in % of full weight per second
#define JUMP_ACCEL 30.0f       // character jump acceleration in upward units per squared second�����ٶȣ�
#define GRAVITY 90.0f          // gravity in downward units per squared second
#define ACTION_LENGTH  5       //action���еĳ���   
#define REACT_TIME 0.2f          
class PlayerCharacterController
{
private:

	// all the animations our character has, and a null ID
	// some of these affect separate body parts and will be blended together
	//enum AnimID
	//{
	//	//ANIM_IDLE_BASE,
	//	//ANIM_IDLE_TOP,
	//	//ANIM_RUN_BASE,
	//	//ANIM_RUN_TOP,
	//	//ANIM_HANDS_CLOSED,
	//	//ANIM_HANDS_RELAXED,
	//	//ANIM_DRAW_SWORDS,
	//	//ANIM_SLICE_VERTICAL,
	//	//ANIM_SLICE_HORIZONTAL,
	//	//ANIM_DANCE,
	//	//ANIM_JUMP_START,
	//	//ANIM_JUMP_LOOP,
	//	//ANIM_JUMP_END,
	//	//ANIM_NONE
	//};

	enum AnimID
	{
		ANIM_Death_BASE,
		/*ѭ������*/
		ANIM_Waiting_Stance_BASE,
		ANIM_Run_BASE,
		ANIM_Walk_Forward_BASE,
		ANIM_Walk_Right_BASE,
		ANIM_Walk_Left_BASE,
		ANIM_Walk_Back_BASE,

		/*��ѭ������*/
		ANIM_Attack_Center_BASE,
		ANIM_Attack_Right_BASE,
		ANIM_Attack_Left_BASE,
		ANIM_Attack_Down_BASE,
		/*�ս��*/
		ANIM_Attack_big,
		ANIM_Attack_big_b,
		ANIM_NONE
	};



public:
	
	PlayerCharacterController(Camera* cam)
	{
		setupBody(cam->getSceneManager());
		mBodyNode->setScale(0.15,0.15,0.15);
		setRun(false);
		setupCamera(cam);

		setupAnimations();
	}

	void setRun(bool t)
	{
		isRun=t;
	}

	void addTime(Real deltaTime)
	{
		updateBody(deltaTime);
		updateAnimations(deltaTime);
	//	updateCamera(deltaTime);
	}

	int getCurrentAction()
	{
		return this->mBaseAnimID;//mAnimslevel[this->mBaseAnimID];
	}

	void injectKeyDown(const OIS::KeyEvent& evt) //isRun ��ʾ�Ƿ��ڱ���״̬
	{

		//if (evt.key == OIS::KC_Q && (mTopAnimID == ANIM_IDLE_TOP || mTopAnimID == ANIM_RUN_TOP))
		//{
		//	// take swords out (or put them back, since it's the same animation but reversed)
		//	setTopAnimation(ANIM_DRAW_SWORDS, true);
		//	mTimer = 0;
		//}
		//else if (evt.key == OIS::KC_E && !mSwordsDrawn)
		//{
		//	if (mTopAnimID == ANIM_IDLE_TOP || mTopAnimID == ANIM_RUN_TOP)
		//	{
		//		// start dancing
		//		setBaseAnimation(ANIM_DANCE, true);
		//		setTopAnimation(ANIM_NONE);
		//		// disable hand animation because the dance controls hands
		//		mAnims[ANIM_HANDS_RELAXED]->setEnabled(false);
		//	}
		//	else if (mBaseAnimID == ANIM_DANCE)
		//	{
		//		// stop dancing
		//		setBaseAnimation(ANIM_IDLE_BASE);
		//		setTopAnimation(ANIM_IDLE_TOP);
		//		// re-enable hand animation
		//		mAnims[ANIM_HANDS_RELAXED]->setEnabled(true);
		//	}
		//}
		
		if(death == 1) 
			return;
		//mine:
		KeyState=evt.key;
		switch(evt.key)
			{
			case OIS::KC_UP : setBaseAnimation(ANIM_Walk_Forward_BASE ,false);//ANIM_Walk_Forward_BASE&&isRun? ANIM_Run_BASE:
				mAnims[ANIM_Walk_Forward_BASE]->setLoop(true);
				mKeyDirection.z = -1;
				break;
			case OIS::KC_LEFT : setBaseAnimation(ANIM_Walk_Left_BASE, false);
				mAnims[ANIM_Walk_Left_BASE]->setLoop(true);
				mKeyDirection.x = -1;
				break;
			case OIS::KC_DOWN : setBaseAnimation(ANIM_Walk_Back_BASE, false);
				mAnims[ANIM_Walk_Back_BASE]->setLoop(true);
				mKeyDirection.z = 1;
				break;
			case OIS::KC_RIGHT : setBaseAnimation(ANIM_Walk_Right_BASE, false);
				mAnims[ANIM_Walk_Right_BASE]->setLoop(true);
				mKeyDirection.x = 1;
				break;
			case OIS::KC_W :
				action[action_rear]='W';
				action_rear=(action_rear+1)%ACTION_LENGTH;
				if(action_rear==action_front) action_front=(action_front+1)%ACTION_LENGTH;
				action_num=(action_num+1)%(ACTION_LENGTH+1);
				this->KeyTimer=REACT_TIME;
				break;
			case OIS::KC_A :
				action[action_rear]='A';
				action_rear=(action_rear+1)%ACTION_LENGTH;
				if(action_rear==action_front) action_front=(action_front+1)%ACTION_LENGTH;
				action_num=(action_num+1)%(ACTION_LENGTH+1);
				this->KeyTimer=REACT_TIME;
				break;
			case OIS::KC_S :
				action[action_rear]='S';
				action_rear=(action_rear+1)%ACTION_LENGTH;
				if(action_rear==action_front) action_front=(action_front+1)%ACTION_LENGTH;
				action_num=(action_num+1)%(ACTION_LENGTH+1);
				this->KeyTimer=REACT_TIME;
				break;
			case OIS::KC_D :
				action[action_rear]='D';
				action_rear=(action_rear+1)%ACTION_LENGTH;
				if(action_rear==action_front) action_front=(action_front+1)%ACTION_LENGTH;
				action_num=(action_num+1)%(ACTION_LENGTH+1);
				this->KeyTimer=REACT_TIME;
				break;
			default:
				break;
			}
		// keep track of the player's intended direction

		//else if (evt.key == OIS::KC_SPACE && (mTopAnimID == ANIM_IDLE_TOP || mTopAnimID == ANIM_RUN_TOP))
		//{
		//	// jump if on ground
		//	setBaseAnimation(ANIM_JUMP_START, true);
		//	setTopAnimation(ANIM_NONE);
		//	mTimer = 0;
		//}

		if (!mKeyDirection.isZeroLength() && mBaseAnimID == ANIM_Waiting_Stance_BASE)
		{
			// start running if not already moving and the player wants to move
			setBaseAnimation(ANIM_Waiting_Stance_BASE, true);
			
			//if (mTopAnimID == ANIM_IDLE_TOP) setTopAnimation(ANIM_RUN_TOP, true);
		}
	}

	void injectKeyUp(const OIS::KeyEvent& evt)
	{

		
		if(death == 1) 
			return;
		// keep track of the player's intended direction
		switch(evt.key)
			{
		case OIS::KC_UP : mAnims[ANIM_Walk_Forward_BASE]->setEnabled(false);
				 mKeyDirection.z = 0;
				break;
		case OIS::KC_LEFT:  mAnims[ANIM_Walk_Left_BASE]->setEnabled( false);
				mKeyDirection.x = 0;
				break;
		case OIS::KC_DOWN : mAnims[ANIM_Walk_Back_BASE]->setEnabled(false);
				mKeyDirection.z = 0;
				break;
		case OIS::KC_RIGHT : mAnims[ANIM_Walk_Right_BASE]->setEnabled(false);
				mKeyDirection.x = 0;
				break;
		case (OIS::KC_LSHIFT||OIS::KC_RSHIFT):
			isRun=false;
			break;
			default: break;
			}
			//mine:
		if(!this->mAnimslevel[this->mBaseAnimID]&&mKeyDirection.z>0) 
		{
			setBaseAnimation(ANIM_Walk_Back_BASE, false);//ANIM_Walk_Back_BASE&&isRun? ANIM_Run_BASE:
			mAnims[ANIM_Walk_Back_BASE]->setLoop(true);//ANIM_Walk_Back_BASE&&isRun? ANIM_Run_BASE:
		}
		if(!this->mAnimslevel[this->mBaseAnimID]&&mKeyDirection.z<0)
		{
			setBaseAnimation(ANIM_Walk_Forward_BASE ,false);//ANIM_Walk_Forward_BASE&&isRun? ANIM_Run_BASE:
			mAnims[ANIM_Walk_Forward_BASE]->setLoop(true);//ANIM_Walk_Forward_BASE&&isRun? ANIM_Run_BASE:
		}
		if(!this->mAnimslevel[this->mBaseAnimID]&&mKeyDirection.x>0)
		{
			setBaseAnimation(ANIM_Walk_Right_BASE, false);//ANIM_Walk_Right_BASE&&isRun? ANIM_Run_BASE:
			mAnims[ANIM_Walk_Right_BASE]->setLoop(true);//ANIM_Walk_Right_BASE&&isRun? ANIM_Run_BASE:

		}
		if(!this->mAnimslevel[this->mBaseAnimID]&&mKeyDirection.x<0)
		{
			setBaseAnimation(ANIM_Walk_Left_BASE, false);//ANIM_Walk_Left_BASE&&isRun? ANIM_Run_BASE:
			mAnims[ANIM_Walk_Left_BASE]->setLoop(true);//ANIM_Walk_Left_BASE&&isRun? ANIM_Run_BASE:
		}

		//if(mAnims[mBaseAnimID]->hasEnded()) setBaseAnimation(ANIM_Waiting_Stance_BASE);
		if (mKeyDirection.isZeroLength() && mBaseAnimID != ANIM_Waiting_Stance_BASE)
		{
			// stop running if already moving and the player doesn't want to move
			setBaseAnimation(ANIM_Waiting_Stance_BASE,true);
			//if (mTopAnimID == ANIM_RUN_TOP) setTopAnimation(ANIM_IDLE_TOP);
		}
		
	}

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
	void injectMouseMove(const OIS::MultiTouchEvent& evt)
	{
		// update camera goal based on mouse movement
		updateCameraGoal(-0.05f * evt.state.X.rel, -0.05f * evt.state.Y.rel, -0.0005f * evt.state.Z.rel);
	}

	void injectMouseDown(const OIS::MultiTouchEvent& evt)
	{
		if (mSwordsDrawn && (mTopAnimID == ANIM_IDLE_TOP || mTopAnimID == ANIM_RUN_TOP))
		{
			// if swords are out, and character's not doing something weird, then SLICE!
            setTopAnimation(ANIM_SLICE_VERTICAL, true);
			mTimer = 0;
		}
	}
#else
	void injectMouseMove(const OIS::MouseEvent& evt)
	{
		// update camera goal based on mouse movement

		//updateCameraGoal(-0.05f * evt.state.X.rel, -0.05f * evt.state.Y.rel, -0.0005f * evt.state.Z.rel);
	}

	

	void injectMouseDown(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
	{
		MouseState=id;

		/*if(id==OIS::MouseButtonID::MB_Left)
		{
			switch(KeyState)
			{
			case OIS::KC_W : setBaseAnimation(ANIM_Attack_Center_BASE ,false);
				break;
			case OIS::KC_A : setBaseAnimation(ANIM_Attack_Left_BASE, false);
				break;
			case OIS::KC_S : setBaseAnimation(ANIM_Attack_Down_BASE, false);
				break;
			case OIS::KC_D : setBaseAnimation(ANIM_Attack_Right_BASE, false);
				break;
			default : 
				setBaseAnimation(ANIM_Attack_Center_BASE ,false);
				break;
			}
		}*/
		//if (mSwordsDrawn && (mTopAnimID == ANIM_IDLE_TOP || mTopAnimID == ANIM_RUN_TOP))
		//{
		//	// if swords are out, and character's not doing something weird, then SLICE!
		//	if (id == OIS::MB_Left) setTopAnimation(ANIM_SLICE_VERTICAL, true);
		//	else if (id == OIS::MB_Right) setTopAnimation(ANIM_SLICE_HORIZONTAL, true);
		//	mTimer = 0;
		//}
	}
#endif

private:

	void setupBody(SceneManager* sceneMgr)
	{
		// create main model
		mBodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode("Player", Vector3::UNIT_Y * CHAR_HEIGHT);
		
		mBodyEnt = sceneMgr->createEntity("PlayerBody", "juto_Walk.mesh");
		mSword1= sceneMgr->createEntity("Sword","juto_Sword.mesh");
		Ogre::TagPoint*TagSword= mBodyEnt->attachObjectToBone("Weapon",mSword1);
		TagSword->pitch(Ogre::Degree(90));
		////mBodyEnt = sceneMgr->createEntity("SinbadBody", "runs.mesh");
		mBodyEnt->setCastShadows(true);
		mBodyNode->attachObject(mBodyEnt);
		mBodyNode->translate(0,0,40);
		mBodyNode->yaw(Ogre::Degree(180));
		//mBodyNode->setScale(0.2,0.2,0.2);
		//////
		//mBodyNode->setAutoTracking(true);
		////////////////

		//mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("juto_Walk.skeleton"); //
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("juto_Waiting_Stance.skeleton"); //�ȴ�
		//mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("juto_Jump.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("juto_Attack_Base.skeleton");//����
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Attack_Special_13.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("juto_Death.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("juto_Attack_big.skeleton");
		mBodyEnt->refreshAvailableAnimationState();
		action_front=0;
		action_rear=0;
		action_num=0;
		this->KeyTimer=0;
		
		//// create swords and attach to sheath
		//LogManager::getSingleton().logMessage("Creating swords");
		//mSword1 = sceneMgr->createEntity("SinbadSword1", "Sword.mesh");
		//mSword2 = sceneMgr->createEntity("SinbadSword2", "Sword.mesh");
		//mBodyEnt->attachObjectToBone("Sheath.L", mSword1);
		//mBodyEnt->attachObjectToBone("Sheath.R", mSword2);

		LogManager::getSingleton().logMessage("Creating the chains");
		//// create a couple of ribbon trails for the swords, just for fun
		NameValuePairList params;
		params["numberOfChains"] = "2";
		params["maxElements"] = "80";
		//mSwordTrail = (RibbonTrail*)sceneMgr->createMovableObject("RibbonTrail", &params);
		//mSwordTrail->setMaterialName("Examples/LightRibbonTrail");
		//mSwordTrail->setTrailLength(20);
		//mSwordTrail->setVisible(false);
		//sceneMgr->getRootSceneNode()->attachObject(mSwordTrail);


		//for (int i = 0; i < 2; i++)
		//{
		//	mSwordTrail->setInitialColour(i, 1, 0.8, 0);
		//	mSwordTrail->setColourChange(i, 0.75, 1.25, 1.25, 1.25);
		//	mSwordTrail->setWidthChange(i, 1);
		//	mSwordTrail->setInitialWidth(i, 0.5);
		//}

		mKeyDirection = Vector3::ZERO;
		mVerticalVelocity = 0;

		m_raySceneQuery=sceneMgr->createRayQuery( Ogre::Ray(this->mBodyNode->getPosition(),Ogre::Vector3::UNIT_Y));
		clampToTerrain();

		playerInfo = new Ogre::MovableText("playerInfo", "Player\n1500/1500");
		playerInfo->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_ABOVE); // Center horizontally and display above the node
		playerInfo->setCharacterHeight( 9.0f );
		playerInfo->setColor(Ogre::ColourValue(0,1.0,0));
		playerInfo->setGlobalTranslation(Ogre::Vector3(0,25,0));

		getHurt = new Ogre::MovableText("getHurt", "HP");
		getHurt->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_ABOVE); // Center horizontally and display above the node
		getHurt->setCharacterHeight( 20.0f );
		getHurt->setColor(Ogre::ColourValue(0,0,1.0));
		getHurt->setGlobalTranslation(Ogre::Vector3(0,30,0));


		mBodyNode->attachObject(playerInfo);
		mBodyNode->attachObject(getHurt);
		HP = 1500;
		death = 0;
		
	}

	void setupAnimations()
	{
		// this is very important due to the nature of the exported animations
		mBodyEnt->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

		//String animNames[] =
		//{"IdleBase", "IdleTop", "RunBase", "RunTop", "HandsClosed", "HandsRelaxed", "DrawSwords",
		//"SliceVertical", "SliceHorizontal", "Dance", "JumpStart", "JumpLoop", "JumpEnd"};

		String animNames[] = 
		{"juto_Death","juto_Waiting_Stance","juto_Run","juto_Walk_Forward","juto_Walk_Right","juto_Walk_Left","juto_Walk_Back","juto_Attack_Center","juto_Attack_Right","juto_Attack_Left","juto_Attack_Down","juto_Attack_big","juto_Attack_big_b"};
		Real level[]={0,0,0,0,0,0,0,1,1,1,1,1,1};
		String code[]={ "","","","","","","","W","D","A","S","WASD","AWD"};
		//����

		// populate our animation list
		for (int i = 0; i < NUM_ANIMS; i++)
		{
			mAnims[i] = mBodyEnt->getAnimationState(animNames[i]);
			mAnims[i]->setLoop(false);//true);//false
			mAnims[i]->setEnabled(false);
			actionCode[i]=code[i];
			mAnimslevel[i]=level[i];
			mFadingIn[i] = false;
			mFadingOut[i] = false;
		}

		//// start off in the idle state (top and bottom together)
		setBaseAnimation(ANIM_Waiting_Stance_BASE);
		//setTopAnimation(ANIM_IDLE_TOP);

		//// relax the hands since we're not holding anything
		//mAnims[ANIM_HANDS_RELAXED]->setEnabled(true);

		//mSwordsDrawn = false;
	}

	void setupCamera(Camera* cam)
	{
		// create a pivot at roughly the character's shoulder
		//pivot�����ڽ�ɫ�ļ�򴦣���֡ѭ����ͬ�����λ����Զ����
		mCameraPivot = cam->getSceneManager()->getRootSceneNode()->createChildSceneNode();
		
		// this is where the camera should be soon, and it spins around the pivot
		//goal��Ϊpivot���ӽڵ㣬������(0 ,0 , 15)����Ҳ����˵goal��Զ����pivot������
		mCameraGoal = mCameraPivot->createChildSceneNode(Vector3(0, 0, 100));
		// this is where the camera actually is
		mCameraNode = this->mBodyNode->createChildSceneNode();//cam->getSceneManager()->getRootSceneNode()->createChildSceneNode();
		mCameraNode->setPosition(mCameraPivot->getPosition() + mCameraGoal->getPosition()+Ogre::Vector3(0,130,200));
		mCameraNode->yaw(Ogre::Degree(180));

		mCameraPivot->setFixedYawAxis(true);
		mCameraGoal->setFixedYawAxis(true);
		mCameraNode->setFixedYawAxis(true);
		// our model is quite small, so reduce the clipping planes
		cam->setNearClipDistance(0.1);
		cam->setFarClipDistance(10000);
		mCameraNode->attachObject(cam);
		//mCameraNode->setAutoTracking(true);


		//mPivotPitch = 0;
	}
public:
	void updateBody(Real deltaTime)
	{
		if(ifdead())return;
		mGoalDirection = Vector3::ZERO;   // we will calculate this


		this->clampToTerrain();
		if (mKeyDirection != Vector3::ZERO&&mBaseAnimID<=ANIM_Walk_Back_BASE&&mBaseAnimID>=ANIM_Run_BASE)// && mBaseAnimID != ANIM_DANCE)
		{
			// calculate actually goal direction in world based on player's key directions
			mGoalDirection += mKeyDirection.z * mCameraNode->getOrientation().zAxis();
			mGoalDirection += mKeyDirection.x * mCameraNode->getOrientation().xAxis();
			mGoalDirection.y = 0;
			mGoalDirection.normalise();

			Quaternion toGoal = mBodyNode->getOrientation().zAxis().getRotationTo(mGoalDirection);
			
			// calculate how much the character has to turn to face goal direction
			Real yawToGoal = toGoal.getYaw().valueDegrees();
			// this is how much the character CAN turn this frame
			Real yawAtSpeed = yawToGoal / Math::Abs(yawToGoal) * deltaTime * TURN_SPEED;
			// reduce "turnability" if we're in midair/****....Omitted.....****/
			//if (mBaseAnimID == ANIM_JUMP_LOOP) yawAtSpeed *= 0.2f;
			if(isRun)
			{
				// turn as much as we can, but not more than we need to
				if (yawToGoal < 0) yawToGoal = std::min<Real>(0, std::max<Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, yawAtSpeed, 0);
				else if (yawToGoal > 0) yawToGoal = std::max<Real>(0, std::min<Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, 0, yawAtSpeed);

				//mBodyNode->yaw(Degree(yawToGoal));
				mBodyNode->yaw(Degree(-this->mKeyDirection.x*TURN_SPEED*deltaTime/10));
				// move in current body direction (not the goal direction)
				////mBodyNode->translate(0, 0, deltaTime * RUN_SPEED * mAnims[mBaseAnimID]->getWeight(),
				//	Node::TS_LOCAL);
			}
			else
			{	
				mBodyNode->translate(-1*mKeyDirection*WALK_SPEED*deltaTime/mKeyDirection.length(),Ogre::Node::TS_LOCAL);
			}
		}

		
		//if (mBaseAnimID == ANIM_JUMP_LOOP)
		//{
		//	// if we're jumping, add a vertical offset too, and apply gravity
		//	mBodyNode->translate(0, mVerticalVelocity * deltaTime, 0, Node::TS_LOCAL);
		//	mVerticalVelocity -= GRAVITY * deltaTime;
		//	
		//	Vector3 pos = mBodyNode->getPosition();
		//	if (pos.y <= CHAR_HEIGHT)
		//	{
		//		// if we've hit the ground, change to landing state
		//		pos.y = CHAR_HEIGHT;
		//		mBodyNode->setPosition(pos);
		//		setBaseAnimation(ANIM_JUMP_END, true);
		//		mTimer = 0;
		//	}
		//}
		this->clampToTerrain();
	}

	

	void updateAnimations(Real deltaTime)
	{
		if(death) return;
		int i,num,j;
		AnimID id;
		Real baseAnimSpeed = 1;
		//Real topAnimSpeed = 1;
		mTimer += deltaTime;
		KeyTimer-=deltaTime;
		if(this->mAnimslevel[this->mBaseAnimID]>0)
		{
			if(this->mAnims[this->mBaseAnimID]->hasEnded())
			{
				//mBodyNode->translate(0,0,RUN_SPEED*this->mAnims[this->mBaseAnimID]->getLength()/2,Ogre::Node::TS_LOCAL);
				this->setBaseAnimation(this->ANIM_Waiting_Stance_BASE);
			}
		}

		if(KeyTimer<0||action_num>=ACTION_LENGTH) KeyTimer=0;
		//��ȡ��ǰ����
		if(action_num!=0&&KeyTimer<=0)
		{
			if(this->mAnimslevel[this->mBaseAnimID]==0||(this->mAnimslevel[this->mBaseAnimID]!=0&&mTimer<=0))
			{
			String s;
			s.clear();
			for(j=action_front,num=0;num<action_num;num++,j=(j+1)%ACTION_LENGTH)
				{
					s=s+this->action[j];
				}
			for(i=0;i<action_num;i++)
			{
				for(j=int(ANIM_Attack_Center_BASE);j<int(this->ANIM_NONE);j++)
				{
					id=AnimID(j);
					if(this->actionCode[id]==s.substr(i))
						break;
				}
				if(id<this->ANIM_NONE) break;
			}
			if(id<this->ANIM_NONE)
			{
				mTimer=0;
				action_num=0;
				action_front=action_rear;
				this->setBaseAnimation(id,true);
			}
			}
		}
		if(!ifdead() && mTimer>mAnims[mBaseAnimID]->getLength()) mTimer=0;

		//if (mTopAnimID == ANIM_DRAW_SWORDS)
		//{
		//	// flip the draw swords animation if we need to put it back
		//	topAnimSpeed = mSwordsDrawn ? -1 : 1;

		//	// half-way through the animation is when the hand grasps the handles...
		//	if (mTimer >= mAnims[mTopAnimID]->getLength() / 2 &&
		//		mTimer - deltaTime < mAnims[mTopAnimID]->getLength() / 2)
		//	{
		//		// so transfer the swords from the sheaths to the hands
		//		mBodyEnt->detachAllObjectsFromBone();
		//		mBodyEnt->attachObjectToBone(mSwordsDrawn ? "Sheath.L" : "Handle.L", mSword1);
		//		mBodyEnt->attachObjectToBone(mSwordsDrawn ? "Sheath.R" : "Handle.R", mSword2);
		//		// change the hand state to grab or let go
		//		mAnims[ANIM_HANDS_CLOSED]->setEnabled(!mSwordsDrawn);
		//		mAnims[ANIM_HANDS_RELAXED]->setEnabled(mSwordsDrawn);

		//		// toggle sword trails
		//		if (mSwordsDrawn)
		//		{
		//			mSwordTrail->setVisible(false);
		//			mSwordTrail->removeNode(mSword1->getParentNode());
		//			mSwordTrail->removeNode(mSword2->getParentNode());
		//		}
		//		else
		//		{
		//			mSwordTrail->setVisible(true);
		//			mSwordTrail->addNode(mSword1->getParentNode());
		//			mSwordTrail->addNode(mSword2->getParentNode());
		//		}
		//	}

		//	if (mTimer >= mAnims[mTopAnimID]->getLength())
		//	{
		//		// animation is finished, so return to what we were doing before
		//		if (mBaseAnimID == ANIM_IDLE_BASE) setTopAnimation(ANIM_IDLE_TOP);
		//		else
		//		{
		//			setTopAnimation(ANIM_RUN_TOP);
		//			mAnims[ANIM_RUN_TOP]->setTimePosition(mAnims[ANIM_RUN_BASE]->getTimePosition());
		//		}
		//		mSwordsDrawn = !mSwordsDrawn;
		//	}
		//}
		//else if (mTopAnimID == ANIM_SLICE_VERTICAL || mTopAnimID == ANIM_SLICE_HORIZONTAL)
		//{
		//	if (mTimer >= mAnims[mTopAnimID]->getLength())
		//	{
		//		// animation is finished, so return to what we were doing before
		//		if (mBaseAnimID == ANIM_IDLE_BASE) setTopAnimation(ANIM_IDLE_TOP);
		//		else
		//		{
		//			setTopAnimation(ANIM_RUN_TOP);
		//			mAnims[ANIM_RUN_TOP]->setTimePosition(mAnims[ANIM_RUN_BASE]->getTimePosition());
		//		}
		//	}

		//	// don't sway hips from side to side when slicing. that's just embarrassing.
		//	if (mBaseAnimID == ANIM_IDLE_BASE) baseAnimSpeed = 0;
		//}
		//else if (mBaseAnimID == ANIM_JUMP_START)
		//{
		//	if (mTimer >= mAnims[mBaseAnimID]->getLength())
		//	{
		//		// takeoff animation finished, so time to leave the ground!
		//		setBaseAnimation(ANIM_JUMP_LOOP, true);
		//		// apply a jump acceleration to the character
		//		mVerticalVelocity = JUMP_ACCEL;
		//	}
		//}
		//else if (mBaseAnimID == ANIM_JUMP_END)
		//{
		//	if (mTimer >= mAnims[mBaseAnimID]->getLength())
		//	{
		//		// safely landed, so go back to running or idling
		//		if (mKeyDirection == Vector3::ZERO)
		//		{
		//			setBaseAnimation(ANIM_IDLE_BASE);
		//			setTopAnimation(ANIM_IDLE_TOP);
		//		}
		//		else
		//		{
		//			setBaseAnimation(ANIM_RUN_BASE, true);
		//			setTopAnimation(ANIM_RUN_TOP, true);
		//		}
		//	}
		//}

		// increment the current base and top animation times
		if (mBaseAnimID < ANIM_NONE) mAnims[mBaseAnimID]->addTime(deltaTime * baseAnimSpeed);
		//if (mTopAnimID != ANIM_NONE) mAnims[mTopAnimID]->addTime(deltaTime * topAnimSpeed);

		// apply smooth transitioning between our animations
		fadeAnimations(deltaTime);
	}

	void fadeAnimations(Real deltaTime)
	{
		for (int i = 0; i < NUM_ANIMS; i++)
		{
			if (mFadingIn[i])
			{
				// slowly fade this animation in until it has full weight
				Real newWeight = mAnims[i]->getWeight() + deltaTime * ANIM_FADE_SPEED;
				mAnims[i]->setWeight(Math::Clamp<Real>(newWeight, 0, 1));
				if (newWeight >= 1) mFadingIn[i] = false;
			}
			else if (mFadingOut[i])
			{
				// slowly fade this animation out until it has no weight, and then disable it
				Real newWeight = mAnims[i]->getWeight() - deltaTime * ANIM_FADE_SPEED;
				mAnims[i]->setWeight(Math::Clamp<Real>(newWeight, 0, 1));
				if (newWeight <= 0)
				{
					mAnims[i]->setEnabled(false);
					mFadingOut[i] = false;
				}
			}
		}
	}

	void updateCamera(Real deltaTime)
	{
		//		3.֡ѭ���߼�

		//���½�ɫ
		//	ȡ�ð�������ʸ�����������ʸ�����ý�ɫ��positon��direction
		//���������
		//	����Զ����������Ů��pivot�ŵ���ɫ�ļ���ϡ�(Ů���ʥ��ʿgoal����Զ��pivotŮ������󷽣���ͬʱgoal����ɱ��camNodeҲ����������)
		//	��ɱ��camNode���Լ����ٶ���goalǰ��һ��
		//	��ɱ�߽����߶�׼����Ů��pivot(��Ȼpostion����goal�ƽ������Ƿ���ȴ������Զ����������Ů��pivot)

		//����chase������Ļ���ʵ��ԭ��ˮ��ʯ�����޷Ǿ���Ů���ʥ��ʿ����ɱ��ʱ�̽�׷����ɱ�������Ķ�סŮ����Ŀ���ʾ���ݣ����ж�׷��Ů��Ķ�ʿ��


		// place the camera pivot roughly at the character's shoulder
		mCameraPivot->setPosition(mBodyNode->getPosition() + Vector3::UNIT_Y * CAM_HEIGHT);


		////��һ�˳�
		// //! ��pivot��׼��ɫ����ǰ����ע���ʱ�����+Z����ͽ�ɫ��+Z�෴����Ϊ���ʱ��+Z����-Z��
  //  //! �����޸ĺ󣬾������һ��һ�˳Ƶ����������ħ����������
  //  //! W��ʼ���ý�ɫ��������ǰ���ߣ��������������ǰ��
  //  Vector3 front = mCameraPivot->getOrientation().zAxis();
  //  Vector3 goal  = -mBodyNode->getOrientation().zAxis();
  //  Quaternion toGoal = front.getRotationTo(goal);
  //  Real yawToGoal = toGoal.getYaw().valueDegrees();
  //  mCameraPivot->yaw(Degree(yawToGoal) , Node::TS_WORLD );
		////��һ�˳�

		 //move the camera smoothly to the goal
		Vector3 goalOffset = mCameraGoal->_getDerivedPosition() - mCameraNode->getPosition();
		mCameraNode->translate(goalOffset * deltaTime * 9.0f);
		// always look at the pivot
		mCameraNode->lookAt(mCameraPivot->_getDerivedPosition(), Node::TS_WORLD);
	}

	void updateCameraGoal(Real deltaYaw, Real deltaPitch, Real deltaZoom)
	{//3�������ֱ��ǵ�ǰmouse��xyz
		//yaw:��y��
		//pitch����x��
		//roll:��z��
	//MouseMove�¼�Ӱ��
	//pitch ---  ֻӰ��pivot��pitch��
	//yaw ---    ֻӰ��pivot��yaw��
	//zoom --- ֻӰ��goal��local postion��������goal��pivot��z����롣goal��Զ��pivot�����󷽣�Ҳ����ֻ��pivot��z�����ƶ���
	//
	//�����ƶ�ֻ�����pivot��yaw��pitch���Լ�goal��local-z���ƶ���ͬ��ɫ���ƶ���û�й�ϵ�ġ�
	//���յĽ���Ǹı���goal��world�е�position��direction�������Ϊcamera��֡ѭ���д����Ψһ���ݡ�


		mCameraPivot->yaw(Degree(deltaYaw), Node::TS_WORLD);

		// bound the pitch
		if (1||!(mPivotPitch + deltaPitch > 25 && deltaPitch > 0) &&
			!(mPivotPitch + deltaPitch < -60 && deltaPitch < 0))
		{
			mCameraPivot->pitch(Degree(deltaPitch), Node::TS_LOCAL);
			mPivotPitch += deltaPitch;
		}
		//goal��pivot�ľ���
		Real dist = mCameraGoal->_getDerivedPosition().distance(mCameraPivot->_getDerivedPosition());
		Real distChange = deltaZoom * dist;

		// bound the zoom
		if (1||!(dist + distChange < 8 && distChange < 0) &&
			!(dist + distChange > 25 && distChange > 0))
		{
			mCameraGoal->translate(0, 0, distChange, Node::TS_LOCAL);
		}
	}

	void setBaseAnimation(AnimID id, bool reset = false)
	{
		if (mBaseAnimID >= 0 && mBaseAnimID < NUM_ANIMS)
		{
			// if we have an old animation, fade it out
			mFadingIn[mBaseAnimID] = false;
			mFadingOut[mBaseAnimID] = true;
		}

		mBaseAnimID = id;

		if (id <ANIM_NONE)
		{
			// if we have a new animation, enable it and fade it in
			mAnims[id]->setEnabled(true);
			//mine
			mAnims[id]->setTimePosition(mTimer);
			mAnims[id]->setWeight(0);
			mFadingOut[id] = false;
			mFadingIn[id] = true;
			if (reset) mAnims[id]->setTimePosition(0);
		}
	}

	//void setTopAnimation(AnimID id, bool reset = false)
	//{
	//	if (mTopAnimID >= 0 && mTopAnimID < NUM_ANIMS)
	//	{
	//		// if we have an old animation, fade it out
	//		mFadingIn[mTopAnimID] = false;
	//		mFadingOut[mTopAnimID] = true;
	//	}

	//	mTopAnimID = id;

	//	if (id != ANIM_NONE)
	//	{
	//		// if we have a new animation, enable it and fade it in
	//		mAnims[id]->setEnabled(true);
	//		mAnims[id]->setWeight(0);
	//		mFadingOut[id] = false;
	//		mFadingIn[id] = true;
	//		if (reset) mAnims[id]->setTimePosition(0);
	//	}
	//}
void clampToTerrain()
{
	static Ogre::Ray updateRay;
	updateRay.setOrigin(this->mBodyNode->getPosition()+Ogre::Vector3(0,0,0));
	updateRay.setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);
	m_raySceneQuery->setRay(updateRay);
	Ogre::RaySceneQueryResult &Result= m_raySceneQuery->execute();

	if(Result.size() == 0)
	{
		updateRay.setOrigin(this->mBodyNode->getPosition());
		updateRay.setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);
		m_raySceneQuery->setRay(updateRay);
		Result = m_raySceneQuery->execute();
	}

	Ogre::RaySceneQueryResult ::iterator i=Result.begin();
	while(i!=Result.end()&&i->movable->getMovableType()!="Entity") i++;
	if(i!= Result.end()&& i->movable)
	{
		this->mBodyNode->setPosition(this->mBodyNode->getPosition().x,this->mBodyNode->getPosition().y+i->distance*m_raySceneQuery->getRay().getDirection().y ,this->mBodyNode->getPosition().z);
		//mCamera->setPosition(0,0,0);
	}
}


public:
	Ogre::AxisAlignedBox getAABB()
	{
		return mBodyNode->_getWorldAABB();
	}


	void setInfo(Ogre::String str)
	{
		playerInfo->setCaption(str);
	}


	void setHurtInfo(Ogre::String str)
	{
		getHurt->setCaption(str);
	}

	void stopAnim()
	{
		this->setBaseAnimation(this->ANIM_Waiting_Stance_BASE);
		//updateAnimations(0);
		//fadeAnimations(0);
	}
	
	Real getHP()
	{
		return this->HP;
	}
	void setHP(Real hp)
	{
		this->HP = hp;
	}

	Real getAttack()
	{
		Real attack = 0;
		if(mAnims[mBaseAnimID]->hasEnded())
		{
			switch(mBaseAnimID)
			{
			case ANIM_Attack_Center_BASE:
				attack = 2;
				break;
			case ANIM_Attack_Down_BASE:
				attack = 3;
				break;
			case ANIM_Attack_Left_BASE:
				attack = 8;
				break;
			case ANIM_Attack_Right_BASE:
				attack = 6;
				break;
			case ANIM_Attack_big:
				attack = 3;
				break;
			case ANIM_Attack_big_b:
				attack = 19;
				break;
			default:
				attack = 0;
			}
		}

		return attack;
	}

	bool ifdead()
	{

		if(HP <= 0)
		{

			setBaseAnimation(ANIM_Death_BASE,false);
			mAnims[ANIM_Death_BASE]->setLoop(false);
			if(mAnims[ANIM_Death_BASE]->hasEnded())
				death = 1;
			return true;	
		}
		else return false;
	}
private:
	int death;
	Ogre::MovableText* playerInfo;
	Ogre::MovableText* getHurt;
	Camera* mCamera;
	SceneNode* mBodyNode;
	SceneNode* mCameraPivot;
	SceneNode* mCameraGoal;
	SceneNode* mCameraNode;
	Real mPivotPitch;
	Entity* mBodyEnt;
	Entity* mSword1;
	RaySceneQuery * m_raySceneQuery;
	//Entity* mSword2;
	//RibbonTrail* mSwordTrail;
	AnimationState* mAnims[NUM_ANIMS];    // master animation list
	Real mAnimslevel[NUM_ANIMS];          //�������ȼ�
	AnimID mBaseAnimID;                   // current base (full- or lower-body) animation
	//AnimID mTopAnimID;                    // current top (upper-body) animation
	bool mFadingIn[NUM_ANIMS];            // which animations are fading in
	bool mFadingOut[NUM_ANIMS];           // which animations are fading out
	//bool mSwordsDrawn;
	Vector3 mKeyDirection;      // player's local intended direction based on WASD keys
	Vector3 mGoalDirection;     // actual intended direction in world-space
	Real mVerticalVelocity;     // for jumping
	Real mTimer;                // general timer to see how long animations have been playing
	Real KeyTimer;              // ���ڴ���������붯���ļ��
	OIS::KeyCode KeyState;
	OIS::MouseButtonID MouseState;
	char action[ACTION_LENGTH];//�������
	String actionCode[NUM_ANIMS];
	Vector3 SwordPosition;
	int action_front;
	int action_rear;
	int action_num;
	bool isRun;
	




	Real HP;
};

#endif
