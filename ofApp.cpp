#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->frame.clear();

	auto R = 250.f;
	auto r = 100.f;
	auto u_step = 8.f;
	auto v_step = 2.f;

	auto v_start = 0.f;
	auto v_len = 80.f;

	for (int i = 0; i < 2; i++) {

		for (auto r = 10; r <= 80; r += 5) {

			v_start = (ofGetFrameNum() +  r) % 360 + i * 180;
			auto start_index = this->frame.getNumVertices();

			for (auto v = v_start; v < v_start + v_len; v += v_step) {

				vector<glm::vec3> vertices{
					glm::vec3(this->make_point(R, r, v * u_step, v)),
					glm::vec3(this->make_point(R, r, (v + v_step) * u_step, v + v_step)),
					glm::vec3(this->make_point(R, r, v * u_step, v + v_step)),
					glm::vec3(this->make_point(R, r, (v - v_step) * u_step, v))
				};

				auto index = this->face.getNumVertices();

				this->face.addVertices(vertices);
				this->frame.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
				this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

				this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
				this->frame.addIndex(index + 2); this->frame.addIndex(index + 3);

				for (int k = 0; k < 4; k++) {

					i == 0 ? this->face.addColor(ofColor(39)) : this->face.addColor(ofColor(239));
					i == 0 ? this->frame.addColor(ofColor(239)) : this->frame.addColor(ofColor(39));
				}
			}

			this->frame.addIndex(start_index + 1); this->frame.addIndex(start_index + 3);
			this->frame.addIndex(this->frame.getNumVertices() - 3); this->frame.addIndex(this->frame.getNumVertices() - 2);
		}
	}
}


//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->face.draw();
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}