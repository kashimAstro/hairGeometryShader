#include "var.h"
#include "ofxAssimpModelLoader.h"

class xApp : public ofBaseApp{

	public:
		ofxAssimpModelLoader model;

		void mouseMoved(int x, int y){
    			model.setPausedForAllAnimations(true);
		        animationPosition = x / (float)ofGetHeight();
			bAnimateMouse = true;
        		animationPosition = x / (float)ofGetHeight();
		}

		void mouseReleased(int x, int y, int button){
		    if(bAnimate) {
		        model.setPausedForAllAnimations(false);
		    }
		    bAnimateMouse = false;
		}

		void setup() {
		        ofSetFrameRate(60);
		        ofSetVerticalSync(true);
			bAnimate = false;
			bAnimateMouse = false;
			animationPosition = 0;
			model.loadModel("model/model.dae");
			model.setPosition( ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0 );
			model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
			model.playAllAnimations();
			if(!bAnimate) {
			        model.setPausedForAllAnimations(true);
			}

			w=ofGetScreenWidth();
			h=ofGetScreenHeight();
		        shader.setGeometryInputType(GL_LINES);
		        shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
		        shader.setGeometryOutputCount((5 + 1) * (4 + 1) * 2);
		        shader.load( "shaders/vertex.glsl", "shaders/fragment.glsl", "shaders/geom_hair.glsl");
		        printf("Maximum number of output vertices support is: %i\n", shader.getGeometryMaxOutputCount());
			camera.setFarClip(100000);
		}

		void update() {
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
			model.update();
			if(bAnimateMouse) {
			        model.setPositionForAllAnimations(animationPosition);
			}
//			camera.setPosition( ofVec3f(-0.184568, 7.31754, 33.8837) );
		}

		void draw() {
			ofBackgroundGradient( ofColor(210), ofColor(10));
			ofEnableDepthTest();
			camera.begin();
			shader.begin();
			shader.setUniform1f("hairLeng",2.6); //(ofGetFrameNum()%10);
		      	shader.setUniform1f("time", ofGetElapsedTimef() ); /* use for noise in geometry shader */
			shader.setUniformMatrix4f("projection",camera.getProjectionMatrix());
			shader.setUniformMatrix4f("modelview", camera.getModelViewMatrix() );
			if(sphere)
				  ofDrawSphere(180);
			else{
				  ofPushMatrix();
				  ofTranslate(model.getPosition().x+100, model.getPosition().y, 60);
				  ofTranslate(-model.getPosition().x, -model.getPosition().y, 60);
				  model.drawFaces();
				  ofPopMatrix();
			}
			shader.end();
			ofDisableDepthTest();
			camera.end();
		}

		void keyPressed(int key) {
			ofPoint modelPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75);
			if(key == 'q') cout<<camera.getPosition()<<endl; 
		        switch (key) {
				case 'f':
					ofToggleFullscreen();
					break;
				case '1':
					model.loadModel("model/monster-animated-character-X.X");
					model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
				        model.setRotation(0, -90, 0, 0, 1);
					sphere=false;
					break;
				case '2':
					model.loadModel("model/TurbochiFromXSI.dae");
					model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
                                        model.setRotation(0, -180, 1, 0, 0);
					sphere=false;
					break;
				case '3':
					model.loadModel("model/model.dae");
					model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
					sphere=false;
					break;
				case '4':
					sphere=!sphere;
					break;
		                default:
		                        break;
		        }
		}

};

int main(){
       ofAppGLFWWindow window;
       ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
       ofRunApp( new xApp());
}
