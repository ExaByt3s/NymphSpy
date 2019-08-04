#pragma once

class string {
private:
	uint8_t* m_data = 0;
	size_t m_length = 0;

public:
	string() { m_data = (uint8_t*)malloc(0); }

	string(char _var) {
		m_length = 2;
		m_data = (uint8_t*)malloc(m_length);
		memcpy_s(m_data, m_length, &_var, sizeof(_var));
		m_data[m_length - 1] = '\0';
	}

	string(char* _var) {
		m_length = strlen(_var) + 1;
		m_data = (uint8_t*)malloc(m_length);
		memcpy_s(m_data, m_length, _var, m_length - 1);
		m_data[m_length - 1] = '\0';
	}

	string(const char* _var) {
		m_length = strlen(_var) + 1;
		m_data = (uint8_t*)malloc(m_length);
		memcpy_s(m_data, m_length, _var, m_length - 1);
		m_data[m_length - 1] = '\0';
	}

	string(const string& _var) {
		m_length = _var.length() + 1;
		m_data = (uint8_t*)malloc(m_length);
		memcpy_s(m_data, m_length, _var.to_str(), m_length - 1);
		m_data[m_length - 1] = '\0';
	}

	char  operator[] (unsigned j) const {
		if (j >= m_length) throw 1;
		return m_data[j];
	}

	char& operator[] (unsigned j) {
		if (j >= m_length) throw 1;
		return (char&)m_data[j];
	}

	string& operator=(char _var         ) { string str(_var); return str; }
	string& operator=(char* _var        ) { string str(_var); return str; }
	string& operator=(const char* _var  ) { string str(_var); return str; }
	string& operator=(const string& _var) {
		m_length = _var.length() + 1;
		m_data = (uint8_t*)malloc(m_length);
		memcpy_s(m_data, m_length, _var.to_str(), m_length - 1);
		m_data[m_length - 1] = '\0';
		return *this;
	}

	string& operator+=(char _var) {
		m_length++;
		m_data = (uint8_t*)realloc(m_data, m_length);
		m_data[m_length - 2] = _var;
		m_data[m_length - 1] = '\0';
		return *this;
	}

	string& operator+=(char* _var) {
		size_t a_length = strlen(_var);
		m_length += a_length;
		m_data = (uint8_t*)realloc(m_data, m_length);
		memcpy_s(m_data + (m_length - a_length) - 1, a_length + 1, _var, a_length);
		m_data[m_length - 1] = '\0';
		return *this;
	}

	string& operator+=(const char* _var) {
		size_t a_length = strlen(_var);
		m_length += a_length;
		m_data = (uint8_t*)realloc(m_data, m_length);
		memcpy_s(m_data + (m_length - a_length) - 1, a_length + 1, _var, a_length);
		m_data[m_length - 1] = '\0';
		return *this;
	}

	string& operator+=(const string& _var) {
		size_t a_length = _var.length();
		m_length += a_length;
		m_data = (uint8_t*)realloc(m_data, m_length);
		memcpy_s(m_data + (m_length - a_length) - 1, a_length + 1, _var.to_str(), a_length);
		m_data[m_length - 1] = '\0';
		return *this;
	}

	friend bool operator==(const string& lsp, const string& rsp) { return (lsp.to_str() == rsp.to_str()); }
	friend bool operator==(const string& lsp, char          rsp) { return (lsp == string(rsp)); }
	friend bool operator==(const string& lsp, const char*   rsp) { return (lsp == string(rsp)); }
	friend bool operator==(char          lsp, const string& rsp) { return (string(lsp) == rsp); }
	friend bool operator==(const char*   lsp, const string& rsp) { return (string(lsp) == rsp); }

	friend bool operator!=(const string& lsp, const string& rsp) { return !(lsp == rsp); }
	friend bool operator!=(const string& lsp, char          rsp) { return !(lsp == rsp); }
	friend bool operator!=(const string& lsp, const char*   rsp) { return !(lsp == rsp); }
	friend bool operator!=(char          lsp, const string& rsp) { return !(lsp == rsp); }
	friend bool operator!=(const char*   lsp, const string& rsp) { return !(lsp == rsp); }

	friend string operator+(const string& lsp, const string& rsp) { return string(lsp) += rsp; }
	friend string operator+(const string& lsp, char          rsp) { return string(lsp) += string(rsp); }
	friend string operator+(const string& lsp, const char* rsp  ) { return string(lsp) += string(rsp); }
	friend string operator+(char          lsp, const string& rsp) { return string(lsp) += rsp; }
	friend string operator+(const char*   lsp, const string& rsp) { return string(lsp) += rsp; }

	const char* to_str() const { return (const char*)m_data; }
	size_t length() const { return m_length - 1; }

	~string() { free(m_data); }
};

